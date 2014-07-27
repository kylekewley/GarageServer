#ifndef Garage_Constants_h
#define Garage_Constants_h

#include <string>

using namespace std;

typedef enum {
    GARAGE_META_PARSER_ID = 1000,
    GARAGE_COMMAND_PARSER_ID = 1001,
    GARAGE_STATUS_PARSER_ID = 1002,
    GARAGE_HISTORY_PARSER_ID = 1003
}GarageServerParser;

typedef enum {
    CLIENT_STATUS_PARSER_ID = 9999
}GarageClientParser;

static const string GARAGE_GROUP_ID = "garage";

#endif
