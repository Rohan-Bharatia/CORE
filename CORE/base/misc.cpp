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

#ifndef _BASE_MISC_cpp_
    #define _BASE_MISC_cpp_

#include <iostream>

#include "prerequisites.c"
#include "time.cpp"
#include "io.cpp"

void setVoltage(const uint8_t pin, const float voltage)
{
    isPinDefined(pin);
    int isOn   = pinVoltage[pin] > 3;
    int turnOn = voltage > 3;

    if(pin == AREF)
    {
        reference = voltage;
        return;
    }

    if (interruptsEnabled && ints.find(pin) != ints.end())
    {
        switch(ints[pin].mode)
        {
        case CHANGE:
            if (is_on != turn_on)
                an_ints[pin].intpointer();
            break;
        case RISING:
            if (!is_on && turn_on)
                an_ints[pin].intpointer();
            break;
        case FALLING:
            if (is_on && !turn_on)
                an_ints[pin].intpointer();
            break;
        }
    }
    
    an_pin_voltage[pin] = voltage;
    return;
}

void requestVoltage(const uint8_t pin)
{
    std::cout << "set voltage of pin " << std::to_string(pin) << " to: ";
    float voltage;
    std::cin >> voltage;
    setVoltage(pin, voltage);
    return;
}

inline void printTimestamp()
{
#ifdef DEBUG_TIMESTAMP
    std::cout << millis() << "ms | ";
#endif // DEBUG_TIMESTAMP
    return;
}

// Random Numbers
inline long random(long max)
{
    return rand() % max;
}

inline long random(long min, long max)
{
    return rand() % (max - min) + min;
}

inline void randomSeed(unsigned long seed)
{
    srand(seed);
    return;
}

#endif // _BASE_MISC_cpp_