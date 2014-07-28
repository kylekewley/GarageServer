#include <getopt.h>
#include <sstream>
#include <thread>
#include <PiServer/PiServer.h>

#include "GarageDoorBridge.h"
#include "GarageDoor.h"

#define DEFAULT_PORT_NUMBER     10002
using namespace std;

static struct option longOptions[] = {
    {"port",    required_argument,  0,  'p'}
};



int main(int argc, char **argv) {
    int portNumber = DEFAULT_PORT_NUMBER;


    while (1) {
        int c = getopt_long(argc, argv, "p:", longOptions, NULL);
        if (c == -1)
            break;
        stringstream arg;
        if (optarg)
            arg << optarg;
        switch (c) {
            case 'p':
                int portInput;
                arg >> portInput;
                if (portInput < 1024 || portInput > INT16_MAX) {
                    //Ports lower than 1024 are invalid
                    cerr << "You entered an invalid port. Connecting to default port " << to_string(portNumber) << endl;
                }else {
                    portNumber = portInput;
                }
                break;
            case '?':
                break;
            default:
                cout << "?? getopt returned character code 0" << oct << c << endl;
        }
    }

    PiServer piServer = PiServer();

    //Right now, the bridge just registers parsers with the PiParser object 
    vector<GarageDoor> doors;

    string leftDoorName("Left Door");
    string middleDoorName("Middle Door");

    GarageDoor leftDoor(leftDoorName, 13, 11);
    GarageDoor middleDoor(middleDoorName, 14, 10);

    doors.push_back(leftDoor);
    doors.push_back(middleDoor);

	thread *t1 = new thread([&piServer, portNumber]() mutable {piServer.connectToPort(portNumber); });
    GarageDoorBridge(piServer.getClientManager(), doors);

	delete t1;

    return 0;
}
