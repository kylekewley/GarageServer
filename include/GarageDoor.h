#ifndef Garage_Door_h
#define Garage_Door_h

#include <string>

using namespace std;

class GarageDoor {
    public:
        GarageDoor(string& doorName, int wiringPiInputPin, int wiringPiControlPin):
            doorName(doorName), wiringPiInputPin(wiringPiInputPin), wiringPiControlPin(wiringPiControlPin) {};

        const string& getDoorName() const {return doorName;};
        int getWiringPiInputPin() const {return wiringPiInputPin;};
        int getWiringPiControlPin() const {return wiringPiControlPin;};

        bool getClosed() const {return isClosed;};
        void setClosed(bool closed) {isClosed=closed;};

    private:
        const string doorName;
        const int wiringPiInputPin;
        const int wiringPiControlPin;
        bool isClosed;
};

#endif
