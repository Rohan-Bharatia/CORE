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

#ifdef _CONTROL_SAFETY_cpp_
    #define _CONTROL_SAFETY_cpp_

#include <iostream>
#include <vector>
#include <numeric>

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

// Faults
int voltageFault(const uint8_t pin, const double threshold = DEFAULT_VOLTAGE_THRESHOLD)
{
#ifdef DEBUG_ANALOG_READ
    #undef DEBUG_ANALOG_READ
    #define CDAR
#endif // DEBUG_ANALOG_READ

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
    #define DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

int temperatureFault(FaultStatus* status, const uint8_t pin, const double threshold = DEFAULT_TEMPERATURE_THRESHOLD)
{
#ifdef DEBUG_ANALOG_READ
    #undef DEBUG_ANALOG_READ
    #define CDAR
#endif // DEBUG_ANALOG_READ

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
    #define DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

int sensorTimeoutFault(FaultStatus* status, const uint8_t pin, unsigned long* ms, const double threshold = DEFAULT_SENSOR_TIMEOUT)
{
#ifdef DEBUG_ANALOG_READ
    #undef DEBUG_ANALOG_READ
    #define CDAR
#endif // DEBUG_ANALOG_READ

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
    #define DEBUG_ANALOG_READ
#endif // CDAR

    return status->hasFault;
}

// Limiter
template<typename T>
T limit(T x, T min, T max)
{
    if (x <= min)
    {
        x = min;
    #ifdef DEBUG_LIMITER
        printTimestamp();
        std::cout << "\'x\' has reached the lower limit: " << min << "\n";
    #endif // DEBUG_LIMITER
    }
    if (x >= max)
    {
        x = max;
    #ifdef DEBUG_LIMITER
        printTimestamp();
        std::cout << "\'x\' has reached the upper limit: " << max << "\n";
    #endif // DEBUG_LIMITER
    }

    return x;
}

// Health
template<typename T>
class HealthMonitor
{
public:
    HealthMonitor(void) = default;
    HealthMonitor(std::vector<T> samples = {}, uint32_t max = 100) : samples(samples), max(max)
    {
        return;
    }

    void addSample(T x)
    {
        samples.push_back(x);

        if (samples.size() > max)
            samples.erase(samples.begin())
    #ifdef DEBUG_HEALTH
        printTimestamp();
        std::cout << "Added to samples: " << x << "\n";
    #endif //DEBUG_HEALTH
        return;
    }
    void addSample(std::vector<T> xs)
    {
        for(T x : xs)
            samples.push_back(x);

        if (samples.size() > max)
            samples.erase(samples.begin())
    #ifdef DEBUG_HEALTH
        printTimestamp();
        std::cout << "Added to samples: " << xs << "\n";
    #endif //DEBUG_HEALTH
        return;
    }

    T average() const
    {
        if (samples.empty())
            return (T)0.0;
        T avg = std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
    #ifdef DEBUG_HEALTH
        printTimestamp();
        std::cout << "Average of samples is: " << avg << "\n";
    #endif // DEBUG_HEALTH
        return avg;
    }

    int isUnhealthy(T threshold) const
    {
        if(average() > threshold)
        {
        #ifdef DEBUG_HEALTH
            printTimestamp();
            std::cout << "Average: " << average() << " has passed the threshold: " << threshold << "\n";
        #endif // DEBUG_HEALTH
        }
        return average() > threshold;
    }

private:
    std::vector<T> samples;
    uint32_t max;
};

#endif // _CONTROL_SAFETY_cpp_