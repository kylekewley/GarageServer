#ifndef Garage_Door_Bridge_h
#define Garage_Door_Bridge_h

//From the PiServer library
#include <PiServer/CustomBufferParser.imp.h>
#include <PiServer/ClientManager.h>

//Standard library
#include <utility>

//The sqlite3 library
#include <sqlite3.h>

//WiringPi library
#include <WiringPi/wiringPi.h>

//Protocol Buffers
#include "GarageMetaData.pb.h"
#include "GarageStatus.pb.h"
#include "GarageCommand.pb.h"
#include "GarageHistoryRequest.pb.h"

//The GarageDoor object
#include "GarageDoor.h"

using namespace std;

class GarageDoorBridge {

    public:
        /**
         * Create a GarageDoorBridge instance that will use the clientManager
         * object to send asynchronous messages to clients. It will also register
         * its custom parsers with the PiParser object held by the clientManager.
         *
         * @param clientManager   The manager used to communicate with clients.
         * @param doors     A list of garage door objects to control/monitor.
         */
        GarageDoorBridge(ClientManager& clientManager, vector<GarageDoor>& doors);

        int getDoorCount() const;

        /**
         * Converts the door index in the supplied array to the wiringPi GPIO
         * pin used to detect the door status.
         */
        int doorIndexToPin(int index);

        /**
         * Converts the wiringPi GPIO pin used to detect the door door status
         * to the index of the door in the supplied array.
         */
        int pinToDoorIndex(int pin);

        void triggerGarageDoor(int doorIndex);

        bool garageIsClosed(int doorIndex);

        const vector<GarageDoor>& getDoors();
    private:

        /**
         * Test value for the server.
         * We will need the GPIO pin number for each door
         */
        int doorCount = 2;

        /**
         * The name of the history table
         */
        static const string HISTORY_TABLE_NAME;

        /**
         * The filepath for the database
         */
        static const string HISTORY_DATABASE_PATH;

        /**
         * The ClientManager that is used to send messages to clients.
         */
        ClientManager& clientManager;

        /**
         * sqlite database handle
         */
        sqlite3* database;

        /**
         * A list of garage doors to monitor and control
         */
        vector<GarageDoor> _doors;

        /**
         * Map used to convert from GPIO pin to array index
         */
        map<int, int> pinToIndex;

        typedef enum {
            COLUMN_UNIQUE_ID,
            COLUMN_GARAGE_ID,
            COLUMN_DID_CLOSE,
            COLUMN_TIMESTAMP,
        }HISTORY_COLUMN_NAMES;

        static string getColumnName(HISTORY_COLUMN_NAMES column);
        /**
         * Creates all of the inner class parsers and registers them with
         * the PiParser instance held by the clientManager
         */
        void registerParsers();

        /**
         * This should be called once to convert the doors vector to the 
         * pinToIndex map
         */
        void createPinToIndexMap(const vector<GarageDoor>& doors);

        /* ##Database Methods## */
        /* -------------------- */

        /**
         * Connects to the sqlite database with the given filepath.
         * If no database exists, we will create it and add the default tables.
         *
         * @param   databasePath    The path to the sqlite database.
         * @param   outDb           An sqlite handle to the new database.
         *
         * @discussion  The outDb parameter will be set to NULL if there was an
         * error creating the database.
         *
         * @return  SQLITE_OK or an error code.
         */
        int connectToDatabase(const string& databasePath, sqlite3** outDb);

        /**
         * @param   db          The database handle.
         * @param   tableName   The name of the table to check existence.
         * @param   result      The result of the query.
         *
         * @return  true if the table exists, false if the table doesn't exist
         * or there is an error. If there was an error, the out parameter result
         * will be set to the error code.
         */
        bool tableExists(sqlite3* db, const string& tableName, int* result);

        /**
         * Creates the garage history table in the database.
         *
         * @param   db The database handle.
         *
         * @return  SQLITE_OK or an error code.
         */
        int createHistoryTable(sqlite3* db);


        /* ###Querying the Database### */

        /**
         * Returns an object containing all of the garage history starting at
         * startTime and ending at startTime+timespan.
         *
         * The returned value is owned by the caller. If it is being returned by
         * a CustomBufferParser subclass in the parseBuffer method, it will be
         * deleted by the superclass. Otherwise, it must be deleted explicitly.
         *
         * @param   startTime   The time to start getting garage history data.
         * @param   timespan    The length of time to include in the history.
         *
         * @return A GarageStatus object containing all of the history requested.
         */
        GarageStatus* getGarageHistory(int32_t startTime, int32_t timespan);

        int addGarageHistory(int garageId, bool didClose);

        /**
         * @return  The current unix epoch time in seconds
         */
        uint32_t timeSinceEpoch() const;

        //Needs to be a friend to access database methods
        friend class GarageHistoryParser;

        /**
         * Initialize the GPIO pins and WiringPi library.
         *
         * @return true if successful, false otherwise.
         */
        bool configureHardware();

        /**
         * Adds a history row to the database and notifies any clients of the change.
         *
         * @param didClose  true if the door closed.
         * @param pin       The GPIO input pin where the status changed
         */
        void doorStatusChanged(bool didClose, int pin);


        static void doorInputFalling(int pin, void* ptr);

        static void doorInputRising(int pin, void* ptr);

        void watchGarageStatus();
};

#endif

