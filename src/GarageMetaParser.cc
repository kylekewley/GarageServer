#include "GarageMetaParser.h"

#include <string>

using namespace std;

/* ##Parser Subclasses## */
/* --------------------- */
ProtocolBuffer* GarageMetaParser::
parseBuffer(const GarageMetaData*, int) const {
    GarageMetaData* metaData = new GarageMetaData();

    metaData->set_doorcount(_parent.getDoorCount());

    cout << "Sending back meta data. Garage number: " <<
        to_string(_parent.getDoorCount()) << endl;
    return metaData;
}
