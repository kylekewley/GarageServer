#include "GarageDoorBridge.h"

using namespace std;

GarageDoorBridge::GarageDoorBridge() {

}

ProtocolBuffer *GarageDoorBridge::parseBuffer(const GarageMetaData *data, int clientID) const {
    GarageMetaData *metaData = new GarageMetaData();

    metaData->set_doorcount(doorCount);

    cout << "Sending back meta data. Garage number: " << to_string(doorCount) << endl;
    return metaData;
}
