#include <getopt.h>
#include <sstream>
#include <PiServer/PiServer.h>

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
    
    try {
        PiServer piServer = PiServer(portNumber);
    } catch (exception e) {
        cerr << "PiServer crashed with exception: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
