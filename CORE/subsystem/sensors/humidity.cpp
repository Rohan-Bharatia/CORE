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

#ifndef _SUBSYSTEM_HUMIDITY_cpp_
    #define _SUBSYSTEM_HUMIDITY_cpp_

#include <cmath>
#include <iostream>

#include "prerequisites.c"
#include "thermal.cpp"
#include "base.c"

class Humidity
{
public:
    Humidity(void) = default;
    Humidity(const uint8_t port, double factor = 1.0) : port(port), factor(factor)
    {
        pinMode(port, INPUT);
        return;
    }

    void calibrate(double off)
    {
    #ifdef DEBUG_HUMIDITY
        printTimestamp();
        std::cout << "Calibrate hygrometer by: " << off << "\n";
    #endif // DEBUG_HUMIDITY
        factor += off;
    }

    double getHumidity(void)
    {
    #ifdef DEBUG_HUMIDITY
        printTimestamp();
        std::cout << "Read humidity: " << analogRead(port) * factor << "\n";
    #endif // DEBUG_HUMIDITY
        return analogRead(port) * factor;
    }

    double getTemperature(double temp)
    {
    #ifdef DEBUG_HUMIDITY
        printTimestamp();
        std::cout << "Read temperature: " << getHumidity(temp) << "\n";
    #endif // DEBUG_HUMIDITY
        return getHumidity(temp);
    }

    double getDewPoint(void)
    {
        const double a = 17.27;
        const double b = 237.7;
        double alpha   = (a * getTemperature()) / (b * getTemperature()) + log(getHumidity() / 100.0);
        double out     = (b * alpha) / (a - alpha);
    #ifdef DEBUG_HUMIDITY
        printTimestamp();
        std::cout << "calculate dew point: " << out << "\n";
    #endif // DEBUG_HUMIDITY
        return out;
    }

private:
    const uint8_t pin;
    double factor;
};

#endif // _SUBSYSTEM_HUMIDITY_cpp_