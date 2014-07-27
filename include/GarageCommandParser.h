#ifndef Garage_Command_Parser_h
#define Garage_Command_Bridge_h

#include "GarageDoorBridge.h"
#include "GarageCommand.pb.h"

/**
 * Parser class to handle garage door commands
 */
class GarageCommandParser : public CustomBufferParser<GarageCommand> {

    public:
        GarageCommandParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageCommand*, int clientID) const;

    private:
        GarageDoorBridge& _parent;
};

#endif

