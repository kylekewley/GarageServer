#ifndef Garage_Meta_Parser_h
#define Garage_Meta_Bridge_h

#include "GarageDoorBridge.h"
#include "GarageMetaData.pb.h"

/**
 * Parser class to handle meta data requests
 */
class GarageMetaParser : public CustomBufferParser<GarageMetaData> {

    public:
        GarageMetaParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageMetaData*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
};

#endif

