#ifndef Garage_History_Parser_h
#define Garage_History_Bridge_h

#include "GarageDoorBridge.h"
#include "GarageHistoryRequest.pb.h"

/**
 * Parser class to handle garage history requests
 */
class GarageHistoryParser : public CustomBufferParser<GarageHistoryRequest> {

    public:
        GarageHistoryParser(GarageDoorBridge& parent): _parent(parent) {};

        ProtocolBuffer* parseBuffer(const GarageHistoryRequest* history, int clientID) const;

    private:
        GarageDoorBridge& _parent;

};

#endif

