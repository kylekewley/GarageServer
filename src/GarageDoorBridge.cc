#include "GarageDoorBridge.h"

//standard library
#include <sstream>

//Constants
#include "GarageConstants.h"

//Parsers
#include "GarageStatusParser.h"
#include "GarageMetaParser.h"
#include "GarageCommandParser.h"
#include "GarageHistoryParser.h"


using namespace std;

const string GarageDoorBridge::HISTORY_TABLE_NAME = "garage_history";
const string GarageDoorBridge::HISTORY_DATABASE_PATH = "./history_db.sqlite";

string GarageDoorBridge::getColumnName(HISTORY_COLUMN_NAMES column) {
    string result = string();
    switch(column) {
        case COLUMN_UNIQUE_ID:
            result = string("unique_id");
            break;
        case COLUMN_TIMESTAMP:
            result = string("timestamp");
            break;
        case COLUMN_DID_CLOSE:
            result = string("did_close");
            break;
        case COLUMN_GARAGE_ID:
            result = string("garage_id");
            break;
    }

    return result;
}

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

int GarageDoorBridge::getDoorCount() const {
    return doorCount;
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
    query << "CREATE TABLE IF NOT EXISTS " << HISTORY_TABLE_NAME << " ("
        << getColumnName(COLUMN_UNIQUE_ID) << " INTEGER PRIMARY KEY, "
        << getColumnName(COLUMN_GARAGE_ID) << " INTEGER DEFAULT (-1), "
        << getColumnName(COLUMN_DID_CLOSE) << " BOOLEAN NOT NULL, "
        << getColumnName(COLUMN_TIMESTAMP) << " INTEGER DEFAULT(strftime('%s', 'now')));" 
        << endl;

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
    query << "SELECT * FROM " << HISTORY_TABLE_NAME << " "
        << "WHERE " << getColumnName(COLUMN_TIMESTAMP) << " BETWEEN ? AND ?;";

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
        int64_t rowId = sqlite3_column_int64(preparedStatement, COLUMN_UNIQUE_ID);
        int garageId = sqlite3_column_int(preparedStatement, COLUMN_GARAGE_ID);
        bool didClose = sqlite3_column_int(preparedStatement, COLUMN_DID_CLOSE) != 0;
        int32_t timestamp = sqlite3_column_int(preparedStatement, COLUMN_TIMESTAMP);

        GarageStatus_DoorStatus* door = garageStatus->add_doors();
        door->set_garageid(garageId);
        door->set_isclosed(didClose);
        door->set_timestamp(timestamp);
        door->set_uniqueid((uint32_t)rowId);
    }
    sqlite3_finalize(preparedStatement);

    return garageStatus;
}

int GarageDoorBridge::addGarageHistory(int garageId, bool didClose) {
    stringstream query;
    query << "INSERT INTO " << HISTORY_TABLE_NAME << " (" 
          << getColumnName(COLUMN_GARAGE_ID) << ", "
          << getColumnName(COLUMN_DID_CLOSE) << ") "
          << "VALUES (" 
          << to_string(garageId) << ", "
          << to_string(didClose) << ");";

    sqlite3_stmt* preparedStatement;
    int result = sqlite3_prepare_v2(database, query.str().c_str(), query.str().length(), &preparedStatement, NULL);
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

