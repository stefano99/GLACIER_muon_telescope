#include "clock_internal.hpp"

bool Clock_internal::begin() {
    RTC.begin();

    return true;
}

bool Clock_internal::sync(int ntp) {
    RTCTime time = RTCTime(ntp);

    RTC.setTime(time);

    #if DEBUG == 1
        RTC.getTime(time);
        Serial.println("clk: initialized. Time: " + String(time));
    #endif

    return true;
}

String Clock_internal::getDate() {
    RTCTime time;
    RTC.getTime(time);

    return time;
}