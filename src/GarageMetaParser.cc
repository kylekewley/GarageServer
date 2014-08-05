#include "GarageMetaParser.h"

#include <string>

#include "GarageDoor.h"

using namespace std;

/* ##Parser Subclasses## */
/* --------------------- */
ProtocolBuffer* GarageMetaParser::
parseBuffer(const GarageMetaData*, int) const {
    GarageMetaData* metaData = new GarageMetaData();

    const vector<GarageDoor>& doors = _parent.getDoors();

    int index = 0;
    for (const GarageDoor& door : doors) {
        GarageMetaData_GarageDoor* addDoor = metaData->add_doors();

        addDoor->set_positionid(index);
        addDoor->set_doorname(door.getDoorName());

        ++index;
    }

    cout << "Sending back meta data. Garage number: " <<
        to_string(_parent.getDoorCount()) << endl;
    return metaData;
}
