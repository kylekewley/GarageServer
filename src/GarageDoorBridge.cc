#include "GarageDoorBridge.h"

//Constants
#include "GarageConstants.h"

//Protocol Buffers
#include "GarageMetaData.pb.h"
#include "GarageStatus.pb.h"
#include "GarageCommand.pb.h"

using namespace std;

GarageDoorBridge::GarageDoorBridge(ClientManager& clientManager): clientManager(clientManager) {
    //Register the default parsers
    registerParsers();
}

void GarageDoorBridge::registerParsers() {
    shared_ptr<CustomParser> garageMetaParser(new GarageMetaParser(*this));
    clientManager._defaultParser->registerParserForID(garageMetaParser, GARAGE_META_PARSER_ID, GARAGE_META_PARSER_ID);

    shared_ptr<CustomParser> garageStatusParser(new GarageStatusParser(*this));
    clientManager._defaultParser->registerParserForID(garageStatusParser, GARAGE_STATUS_PARSER_ID, GARAGE_STATUS_PARSER_ID);

    shared_ptr<CustomParser> garageCommandParser(new GarageCommandParser(*this));
    clientManager._defaultParser->registerParserForID(garageCommandParser, GARAGE_COMMAND_PARSER_ID, GARAGE_COMMAND_PARSER_ID);
}


ProtocolBuffer* GarageDoorBridge::GarageMetaParser::parseBuffer(const GarageMetaData*, int) const {
    GarageMetaData* metaData = new GarageMetaData();

    metaData->set_doorcount(_parent.doorCount);

    cout << "Sending back meta data. Garage number: " << to_string(_parent.doorCount) << endl;
    return metaData;
}


ProtocolBuffer* GarageDoorBridge::GarageStatusParser::parseBuffer(const GarageStatus*, int) const {
    GarageStatus* status = new GarageStatus();

    for (int i = 0; i < 2; ++i) {
        GarageStatus::DoorStatus* door = status->add_doors();
        door->set_timestamp(1);
        door->set_garageid(i);
        door->set_isclosed((i%2)==0);
    }

    cout << "Sending back garage status data" << endl;

    return status;
}


ProtocolBuffer* GarageDoorBridge::GarageCommandParser::parseBuffer(const GarageCommand*, int) const {
    //TODO: Do something with the garage open command.

    //Just send back a confirmation that we parsed successfully
    return NULL;
}

