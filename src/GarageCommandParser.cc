#include "GarageCommandParser.h"

#include <string>

using namespace std;

ProtocolBuffer* GarageCommandParser::
parseBuffer(const GarageCommand* command, int) const {
    //TODO: Do something with the garage open command.

    cout << "Got a garage trigger request... trigger door "  <<
        to_string(command->garageid()) << endl;
    //Just send back a confirmation that we parsed successfully

    return NULL;
}
