#ifndef Garage_Door_Bridge_h
#define Garage_Door_Bridge_h

//From the PiServer library
#include <PiServer/CustomBufferParser.imp.h>
#include <PiServer/ClientManager.h>

//Standard library
#include <utility>

//The sqlite3 library
#include <sqlite3.h>

//Protocol Buffers
#include "GarageMetaData.pb.h"
#include "GarageStatus.pb.h"
#include "GarageCommand.pb.h"
#include "GarageHistoryRequest.pb.h"

using namespace std;

class GarageDoorBridge {

public:
    /**
     * Create a GarageDoorBridge instance that will use the clientManager
     * object to send asynchronous messages to clients. It will also register
     * its custom parsers with the PiParser object held by the clientManager.
     *
     * @param clientManager   The manager used to communicate with clients.
     */
     GarageDoorBridge(ClientManager& clientManager);

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

    /* ##Simple Helper Methods## */
    /* ------------------------- */

    /**
     * @return  The current unix epoch time in seconds
     */
    uint32_t timeSinceEpoch();


    /* ##Inner Parser Classes## */
    /* ------------------------ */

    /**
     * Parser class to handle meta data requests
     */
    class GarageMetaParser : public CustomBufferParser<GarageMetaData> {

    public:
        GarageMetaParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageMetaData*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
    };


    /**
     * Parser class to handle garage status requests
     */
    class GarageStatusParser : public CustomBufferParser<GarageStatus> {

    public:
        GarageStatusParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageStatus*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
    };


    /**
     * Parser class to handle garage door commands
     */
    class GarageCommandParser : public CustomBufferParser<GarageCommand> {

    public:
        GarageCommandParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageCommand*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
    };


    /**
     * Parser class to handle garage history requests
     */
    class GarageHistoryParser : public CustomBufferParser<GarageHistoryRequest> {

    public:
        GarageHistoryParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageHistoryRequest* history, int clientID) const;

    private:
        GarageDoorBridge& _parent;
    };


};

#endif

