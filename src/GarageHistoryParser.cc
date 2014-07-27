#include "GarageHistoryParser.h"

#include <string>
#include <chrono>
using namespace std;

ProtocolBuffer* GarageHistoryParser::
parseBuffer(const GarageHistoryRequest* command, int) const {
    int32_t startTime = timeSinceEpoch(); //The current time
    int32_t interval = -60*60*24; //Negative 24 hours

    if (command->has_starttime() && command->has_interval()) {
        startTime = command->starttime();
        interval = command->interval();
    }else if (command->has_starttime()) {
        //startTime and no interval
        startTime = command->starttime();
        interval = -interval;
    }else if (command->has_interval()) {
        //interval and no startTime
        interval = -abs(command->interval());
    }
    cout << "Requesting history with interval: " << to_string(startTime)
        << " to " << to_string(startTime+interval) << endl;

    GarageStatus* buffer = _parent.getGarageHistory(startTime, interval);
    cout << "Received " << to_string(buffer->doors_size()) << " doors to send." << endl;

    return buffer;
}

/* ##Simple Helper Methods## */
/* ------------------------- */
uint32_t GarageHistoryParser::timeSinceEpoch() const {
    return std::chrono::duration_cast<std::chrono::seconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}
