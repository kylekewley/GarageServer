#include <PiServer/CustomBufferParser.imp.h>

#include "GarageMetaData.pb.h"


class GarageDoorBridge : public CustomBufferParser<GarageMetaData> {
public:
    GarageDoorBridge();

    ProtocolBuffer *parseBuffer(const GarageMetaData *data, int clientID) const;
private:

    int doorCount = 2;
}; 
