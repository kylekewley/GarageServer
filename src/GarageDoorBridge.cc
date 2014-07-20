#include "GarageDoorBridge.h"

//standard library
#include <chrono>
#include <sstream>

//Constants
#include "GarageConstants.h"


using namespace std;

const string GarageDoorBridge::HISTORY_TABLE_NAME = "garage_history";
const string GarageDoorBridge::HISTORY_DATABASE_PATH = "./history_db.sqlite";

GarageDoorBridge::GarageDoorBridge(ClientManager& clientManager):
    clientManager(clientManager) {
    //Register the default parsers
    registerParsers();
    int result = connectToDatabase(HISTORY_DATABASE_PATH, &database);
    cout << "Connection to database " << (result==SQLITE_OK ? "succeeded" : "failed") << " with code " << to_string(result) << endl;
}

void GarageDoorBridge::registerParsers() {
    cout << "Registering parsers for GarageDoorBridge." << endl;

    bool registerSuccess = false;

    //Register the metaParser
    shared_ptr<CustomParser> metaParser(new GarageMetaParser(*this));
    registerSuccess = clientManager._defaultParser->registerParserForID(
            metaParser, GARAGE_META_PARSER_ID, GARAGE_META_PARSER_ID);
    //Print success or failure
    cout << "Registration for GarageMetaParser ID: " <<
        to_string(GARAGE_META_PARSER_ID) << " returned: " <<
        (registerSuccess ? "Success" : "Failue") << endl;

    //Register the statusParser
    shared_ptr<CustomParser> statusParser(new GarageStatusParser(*this));
    registerSuccess = clientManager._defaultParser->registerParserForID(
            statusParser, GARAGE_STATUS_PARSER_ID, GARAGE_STATUS_PARSER_ID);
    //Print success or failure
    cout << "Registration for GarageStatusParser ID: " <<
        to_string(GARAGE_STATUS_PARSER_ID) << " returned: " <<
        (registerSuccess ? "Success" : "Failue") << endl;

    //Register the commandParser
    shared_ptr<CustomParser> commandParser(new GarageCommandParser(*this));
    registerSuccess = clientManager._defaultParser->registerParserForID(
            commandParser, GARAGE_COMMAND_PARSER_ID, GARAGE_COMMAND_PARSER_ID);
    //Print success or failure
    cout << "Registration for GarageCommandParser ID: " <<
        to_string(GARAGE_COMMAND_PARSER_ID) <<
        " returned: " << (registerSuccess ? "Success" : "Failue") << endl;

    //Register the hitoryParser
    shared_ptr<CustomParser> hitoryParser(new GarageHistoryParser(*this));
    registerSuccess = clientManager._defaultParser->registerParserForID(
            hitoryParser, GARAGE_HISTORY_PARSER_ID, GARAGE_HISTORY_PARSER_ID);
    //Print success or failure
    cout << "Registration for GarageHistoryParser ID: " <<
        to_string(GARAGE_HISTORY_PARSER_ID) <<
        " returned: " << (registerSuccess ? "Success" : "Failue") << endl;
}


/* ##Database Methods## */
/* -------------------- */

int GarageDoorBridge::connectToDatabase(const string& databasePath, sqlite3** outDb) {
    int result = sqlite3_open_v2(databasePath.c_str(), outDb,
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (result != SQLITE_OK)
        return result;

    //Create the table if it doesn't exist
    if (!tableExists(*outDb, HISTORY_TABLE_NAME, &result)) {
        if (result != SQLITE_OK) {
            return result;
        }
        //Create the table
        result = createHistoryTable(*outDb);
        if (result != SQLITE_OK)
            return result;
    }


    return SQLITE_OK;
}


bool GarageDoorBridge::tableExists(sqlite3* db, const string& tableName, int* result) {

    string query = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?;";

    sqlite3_stmt* preparedStatement;
    *result = sqlite3_prepare_v2(db, query.c_str(), query.length(), 
            &preparedStatement, NULL);
    if (*result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return false;
    }

    *result = sqlite3_bind_text(preparedStatement, 1, tableName.c_str(), tableName.length(), SQLITE_STATIC);
    if (*result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return false;
    }

    *result = sqlite3_step(preparedStatement);
    if (*result >= SQLITE_ROW) {
        *result = SQLITE_OK;
    }
    if (*result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return false;
    }
    if (sqlite3_column_count(preparedStatement) == 0) {
        sqlite3_finalize(preparedStatement);
        return false;
    }

    int num = sqlite3_column_int(preparedStatement, 0);

    //Clean up
    sqlite3_finalize(preparedStatement);
    return num > 0;
}

int GarageDoorBridge::createHistoryTable(sqlite3* db) {
    stringstream query;
    query << "CREATE TABLE IF NOT EXISTS " << HISTORY_TABLE_NAME
        << " (garage_id INTEGER DEFAULT (-1), "
        << "did_close BOOLEAN NOT NULL, "
        << "timestamp INTEGER DEFAULT(strftime('%s', 'now')));" << endl;

    sqlite3_stmt* preparedStatement;
    int result = sqlite3_prepare_v2(db, query.str().c_str(), query.str().length(), &preparedStatement, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return result;
    }

    result = sqlite3_step(preparedStatement);
    if (result >= SQLITE_ROW) {
        result = SQLITE_OK;
    }
    if (result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return result;
    }

    sqlite3_finalize(preparedStatement);
    return result;
}


/* ###Querying the Database### */

GarageStatus* GarageDoorBridge::getGarageHistory(int32_t startTime, int32_t timespan) {
    stringstream query;
    query << "SELECT ROWID, * FROM " << HISTORY_TABLE_NAME << " "
        << "WHERE timestamp BETWEEN ? AND ?;";

    sqlite3_stmt* preparedStatement;
    int result = sqlite3_prepare_v2(database, query.str().c_str(), query.str().length(), &preparedStatement, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return NULL;
    }

    result = sqlite3_bind_int(preparedStatement, 1, startTime);
    if (result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return NULL;
    }
    result = sqlite3_bind_int(preparedStatement, 2, startTime+timespan);
    if (result != SQLITE_OK) {
        sqlite3_finalize(preparedStatement);
        return NULL;
    }

    GarageStatus* garageStatus = new GarageStatus();

    while (sqlite3_step(preparedStatement) == SQLITE_ROW) {
        int64_t rowId = sqlite3_column_int64(preparedStatement, 0);
        int garageId = sqlite3_column_int(preparedStatement, 1);
        bool didClose = sqlite3_column_int(preparedStatement, 2) != 0;
        int32_t timestamp = sqlite3_column_int(preparedStatement, 3);

        GarageStatus_DoorStatus* door = garageStatus->add_doors();
        door->set_garageid(garageId);
        door->set_isclosed(didClose);
        door->set_timestamp(timestamp);
        door->set_uniqueid((uint32_t)rowId);
    }
    sqlite3_finalize(preparedStatement);

    return garageStatus;
}



/* ##Simple Helper Methods## */
/* ------------------------- */
uint32_t GarageDoorBridge::timeSinceEpoch() {
    return std::chrono::duration_cast<std::chrono::seconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}


/* ##Parser Subclasses## */
/* --------------------- */
ProtocolBuffer* GarageDoorBridge::GarageMetaParser::
parseBuffer(const GarageMetaData*, int) const {
    GarageMetaData* metaData = new GarageMetaData();

    metaData->set_doorcount(_parent.doorCount);

    cout << "Sending back meta data. Garage number: " <<
        to_string(_parent.doorCount) << endl;
    return metaData;
}


ProtocolBuffer* GarageDoorBridge::GarageStatusParser::
parseBuffer(const GarageStatus*, int) const {
    GarageStatus* status = new GarageStatus();

    for (int i = 0; i < 2; ++i) {
        GarageStatus::DoorStatus* door = status->add_doors();
        door->set_timestamp(1);
        door->set_garageid(i);
        door->set_isclosed((i%2)==0);
        //These doors dont need a unique ID but it is a required field
        door->set_uniqueid(0);
    }

    cout << "Sending back garage status data" << endl;

    return status;
}


ProtocolBuffer* GarageDoorBridge::GarageCommandParser::
parseBuffer(const GarageCommand* command, int) const {
    //TODO: Do something with the garage open command.

    cout << "Got a garage trigger request... trigger door "  << 
        to_string(command->garageid()) << endl;
    //Just send back a confirmation that we parsed successfully
    return NULL;
}


ProtocolBuffer* GarageDoorBridge::GarageHistoryParser::
parseBuffer(const GarageHistoryRequest* command, int) const {
    int32_t startTime = _parent.timeSinceEpoch(); //The current time
    int32_t interval = -60*60*24; //Negative 24 hours

    if (command->has_starttime() && command->has_interval()) {
        startTime = command->starttime();
        interval = command->interval();
    }else if (command->has_starttime()) {
        //startTime and no interval
        startTime = command->starttime();
        interval = -interval;
    }else if (command->has_interval()) {
        //interval and no startTime
        interval = -abs(command->interval());
    }
    cout << "Requesting history with interval: " << to_string(startTime)
        << " to " << to_string(startTime+interval) << endl;

    return _parent.getGarageHistory(startTime, interval);
}
