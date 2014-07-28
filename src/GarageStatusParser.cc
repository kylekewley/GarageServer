#include "GarageStatusParser.h"

#include <string>

using namespace std;

ProtocolBuffer* GarageStatusParser::
parseBuffer(const GarageStatus*, int) const {
    GarageStatus* status = new GarageStatus();

    for (int i = 0; i < _parent.getDoorCount(); ++i) {
        GarageStatus::DoorStatus* door = status->add_doors();
        door->set_timestamp(0);
        door->set_garageid(i);
        door->set_isclosed(_parent.garageIsClosed(i));
    }

    cout << "Sending back garage status data" << endl;
    return status;
}
