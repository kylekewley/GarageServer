#ifndef Garage_Door_Bridge_h
#define Garage_Door_Bridge_h

#include <PiServer/CustomBufferParser.imp.h>
#include <PiServer/ClientManager.h>

class GarageMetaData;
class GarageStatus;
class GarageCommand;

class GarageDoorBridge {

public:
    /**
     * Create a GarageDoorBridge instance that will use the clientManager
     * object to send asynchronous messages to clients. It will also register
     * its custom parsers with the PiParser object held by the clientManager.
     *
     * @param clientManager   The manager used to communicate with clients.
     */
     GarageDoorBridge(ClientManager& clientManager);

private:
    /**
     * Test value for the server.
     * We will need the GPIO pin number for each door
     */
    int doorCount = 2;

    /**
     * The ClientManager that is used to send messages to clients.
     */
    ClientManager& clientManager;

    /**
     * Creates all of the inner class parsers and registers them with
     * the PiParser instance held by the clientManager
     */
    void registerParsers();


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

};

#endif

