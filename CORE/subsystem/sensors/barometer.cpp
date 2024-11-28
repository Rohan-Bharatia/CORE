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

#ifndef _SUBSYSTEM_BAROMETER_cpp_
    #define _SUBSYSTEM_BAROMETER_cpp_

#include <cmath>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

enum PressureType
{
    BAR,
    PASCAL,
    PSI
};

enum LengthType
{
    METER,
    KILOMETER,
    FOOT,
    MILE
}

class Barometer
{
public:
    Barometer(void) = default;
    Barometer(const uint8_t pin, double seaLevelPressure = 1013.25) : pin(pin), seaLevelPressure(seaLevelPressure)
    {
        pinMode(pin, INPUT);
        return;
    }

    void setSeaLevelPressure(double pres) : seaLevelPressure(pres)
    {
    #define DEBUG_PRESSURE
        printTimestamp(void);
        std::cout << "Writing sea level pressure: " << pres << "\n";
    #endif // DEBUG_PRESSURE
        return;
    }

    double getPressure(PressureType type = BAR)
    {
        double pres = analogRead(pin);

        switch (type)
        {
        case BAR:
        #define DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading preasure: " << pres << " Bars\n";
        #endif // DEBUG_PRESSURE
            return pres;

        case PASCAL:
            #define DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading preasure: " << pres * 100000 << " Pascals\n";
        #endif // DEBUG_PRESSURE
            return pres * 100000;

        case PSI:
            #define DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading preasure: " << pres * 14.5038 << " PSI\n";
        #endif // DEBUG_PRESSURE
            return pres * 14.5038;
        }
    }

    double getAltitude(LengthType type = METER)
    {
        double alt = 44330.0 * (1.0 - pow(getPressure(BAR) / seaLevelPressure, 0.1903));

        switch (type)
        {
        case METERS:
        #ifdef DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading altitude: " << alt << " meters\n";
        #endif // DEBUG_PRESSURE
            return alt;

        case KILOMETER:
            #ifdef DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading altitude: " << alt / 1000.0 << " kilometers\n";
        #endif // DEBUG_PRESSURE
            return alt / 1000.0;

        case FOOT:
            #ifdef DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading altitude: " << alt * 3.28084 << " feet\n";
        #endif // DEBUG_PRESSURE
            return alt * 3.28084;

        case MILE:
            #ifdef DEBUG_PRESSURE
            printTimestamp(void);
            std::cout << "Reading altitude: " << (alt / 1000.0) * 0.62137119 << " miles\n";
        #endif // DEBUG_PRESSURE
            return (alt / 1000.0) * 0.62137119;
        }
    }

private:
    const uint8_t pin;
    double seaLevelPressure;
};

#endif // _SUBSYSTEM_BAROMETER_cpp_