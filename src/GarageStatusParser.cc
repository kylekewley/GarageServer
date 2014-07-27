#include "GarageStatusParser.h"

#include <string>

using namespace std;

ProtocolBuffer* GarageStatusParser::
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
