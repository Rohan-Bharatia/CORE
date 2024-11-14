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

#ifndef _SUBSYSTEM_THERMAL_cpp_
    #define _SUBSYSTEM_THERMAL_cpp_

#include <deque>

#include "prerequisites.c"
#include "base.c"

enum TemperatureType
{
    CELCIUS,
    FAHRENHEIT,
    KELVIN,
    CENTIGRADE = CELCIUS,
    FILTERED
};

class Thermal
{
public:
    Thermal(void) = default;
    Thermal(const uint8_t port, double offset = 0.0, int size = 5) : port(port), offset(offset), size(size)
    {
        pinMode(port, INPUT);
        return;
    }

    void calibrate(double off)
    {
    #ifdef DEBUG_THERMAL
        printTimestamp();
        std::cout << "Calibrate thermal sensor by: " << off << "\n";
    #endif // DEBUG_THERMAL
        offset += off;
        return;
    }

    double getTemperature(TemperatureType type) const
    {
        double temp = (analogRead(port) / 10.0) + offset;

        switch (type)
        {
        case CELCIUS:
        #ifdef DEBUG_THERMAL
            printTimestamp();
            std::cout << "Read: " << temp << " ° Celcius\n";
        #endif // DEBUG_THERMAL
            return temp;
        
        case FAHRENHEIT:
        #ifdef DEBUG_THERMAL
            printTimestamp();
            std::cout << "Read: " << (temp * 1.8) + 32.0 << " ° Fahrenheit\n";
        #endif // DEBUG_THERMAL
            return (temp * 1.8) + 32.0;

        case KELVIN:
        #ifdef DEBUG_THERMAL
            printTimestamp();
            std::cout << "Read: " << temp + 273.15 << " ° Kelvin\n";
        #endif // DEBUG_THERMAL
            return temp + 273.15;
        
        case CENTIGRADE:
        #ifdef DEBUG_THERMAL
            printTimestamp();
            std::cout << "Read: " << temp << " ° Centigrade\n";
        #endif // DEBUG_THERMAL
            return temp;
        
        case FILTERED:
        #ifdef DEBUG_THERMAL
            printTimestamp();
            std::cout << "Filter: " << applyMovingAverageFilter(temp) << "\n";
        #endif // DEBUG_THERMAL
            return applyMovingAverageFilter(temp);
        }
    }

private:
    double applyMovingAverageFilter(double val)
    {
        if (filter.size() >= size)
            filter.pop_front();
        filter.push_back(analogRead(port));

        double sum = 0.0;
        for (double val : filter)
            sum += val;

        return sum / filter.size();
    }

    const uint8_t pin;
    double offset;
    std::deque<double> filter;
    int size;
};

#endif // _SUBSYSTEM_THERMAL_cpp_