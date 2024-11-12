#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                               ...
//                  Copyright (C) 2024 Rohan Bharatia

#pragma endregion LICENSE

#pragma once

#ifdef _CONTROL_FAULT_cpp_
    #define _CONTROL_FAULT_cpp_

#include "prerequisites.c"
#include "base.c"

#define DEFAULT_VOLTAGE_THRESHOLD     50.0 // Maximum acceptable voltage level
#define DEFAULT_TEMPERATURE_THRESHOLD 75.0 // Maximum safe temperature in Celsius
#define DEFAULT_SENSOR_TIMEOUT        500  // Maximum interval (in ms) before declaring sensor fault

enum FaultType
{
    FAULT_NONE,
    FAULT_HIGH_VOLTAGE,
    FAULT_HIGH_TEMPERATURE,
    FAULT_SENSOR_TIMEOUT
};

struct FaultStatus
{
    int hasFault;
    FaultType type;
};

int voltageFault(const uint8_t pin, const double threshold = DEFAULT_VOLTAGE_THRESHOLD)
{
#ifdef CORE_DEBUG_ANALOG_READ
    #undef CORE_DEBUG_ANALOG_READ
    #define CDAR
#endif // CORE_DEBUG_ANALOG_READ

    FaultStatus* status = { FALSE, FAULT_NONE };
    double voltage = analogRead(pin) * (5.0 / 1023.0);

    if (voltage > threshold)
    {
        status->hasFault = TRUE;
        status->type     = FAULT_HIGH_VOLTAGE;
    }

#ifdef DEBUG_FAULT
    printTimestamp();
    std::cout << "Check pin: " << std::to_string(pin) << " with " << (status->hasFault ? "a" : "no") << " voltage fault detected at " << voltage <<" volts\n";
#endif // DEBUG_FAULT

#ifdef CDAR
    #define CORE_DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

int temperatureFault(FaultStatus* status, const uint8_t pin, const double threshold = DEFAULT_TEMPERATURE_THRESHOLD)
{
#ifdef CORE_DEBUG_ANALOG_READ
    #undef CORE_DEBUG_ANALOG_READ
    #define CDAR
#endif // CORE_DEBUG_ANALOG_READ

    FaultStatus* status = { FALSE, FAULT_NONE };
    double temperature = analogRead(pin) * ((5.0 / 1023.0) * 100.0);

    if (temperature > threshold)
    {
        status->hasFault = TRUE;
        status->type     = FAULT_HIGH_TEMPERATURE;
    }

#ifdef DEBUG_FAULT
    printTimestamp();
    std::cout << "Check pin: " << std::to_string(pin) << " with " << (status->hasFault ? "a" : "no") << " temperature fault detected at " << temperature << " ° Celius\n";
#endif // DEBUG_FAULT

#ifdef CDAR
    #define CORE_DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

int sensorTimeoutFault(FaultStatus* status, const uint8_t pin, unsigned long* ms, const double threshold = DEFAULT_SENSOR_TIMEOUT)
{
#ifdef CORE_DEBUG_ANALOG_READ
    #undef CORE_DEBUG_ANALOG_READ
    #define CDAR
#endif // CORE_DEBUG_ANALOG_READ

    FaultStatus* status = { FALSE, FAULT_NONE };
    
    if(digitalRead(pin) == HIGH)
        ms = millis();

    if (millis() - *ms > threshold)
    {
        status->hasFault = TRUE;
        status->type     = FAULT_SENSOR_TIMEOUT;
    }

#ifdef DEBUG_FAULT
    printTimestamp();
    std::cout << "Check pin: " << std::to_string(pin) << " with " << (status->hasFault ? "a" : "no") << " sensor timeout fault detected at " << millis() - *ms << "Seconds\n";
#endif // DEBUG_FAULT

#ifdef CDAR
    #define CORE_DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

#endif // _CONTROL_FAULT_cpp_