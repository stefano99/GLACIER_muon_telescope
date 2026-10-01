#pragma once
#include "main.h"
#include <Arduino.h>
#include "RTC.h" // TODO: add RTC sync from example project
#include "publisher_mqtt.h"

class Clock_internal {
    public:
        bool begin();
        String getDate();
        bool sync(int ntp);

    protected:
};