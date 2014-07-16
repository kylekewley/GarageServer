#include <PiServer/CustomBufferParser.imp.h>
#include <PiServer/ClientManager.h>

#include "GarageMetaData.pb.h"
#include "GarageStatus.pb.h"

class GarageDoorBridge { 
    public:
        GarageDoorBridge(ClientManager& clientManager);

    private:
        int doorCount = 2;

        ClientManager& clientManager;

        void registerParsers();
        /**
         * Parser class to handle meta data requests
         */
        class GarageMetaParser : public CustomBufferParser<GarageMetaData> {
        public:
            GarageMetaParser(GarageDoorBridge& parent): _parent(parent) {};
                
            ProtocolBuffer *parseBuffer(const GarageMetaData *data, int clientID) const;

        private:
            GarageDoorBridge& _parent;    
        };

        /**
         * Parser class to handle garage status requests
         */
        class GarageStatusParser : public CustomBufferParser<GarageStatus> {
        public:
            GarageStatusParser(GarageDoorBridge& parent): _parent(parent) {};

            ProtocolBuffer *parseBuffer(const GarageStatus *data, int clientID) const;

        private:
            GarageDoorBridge& _parent;
        };
}; 
