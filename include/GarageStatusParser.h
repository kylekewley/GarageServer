#ifndef Garage_Status_Parser_h
#define Garage_Status_Parser_h

#include "GarageDoorBridge.h"
#include "GarageStatus.pb.h"

/**
 * Parser class to handle garage status requests
 */
class GarageStatusParser : public CustomBufferParser<GarageStatus> {

    public:
        GarageStatusParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageStatus*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
};

#endif

