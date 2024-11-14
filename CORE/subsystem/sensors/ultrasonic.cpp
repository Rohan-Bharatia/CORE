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

#ifndef _SUBSYSTEM_ULTRASONIC_cpp_
    #define _SUBSYSTEM_ULTRASONIC_cpp_

#include <iostream>

#include "prerequisites.c"
#include "base.c"

enum DistanceType
{
    CENTIMETER,
    INCH
};

class Ultrasonic
{
public:
    Ultrasonic(void) = default;
    Ultrasonic(const uint8_t triggerPin, const uint8_t echoPin) : triggerPin(triggerPin), echoPin(echoPin)
    {
        pinMode(triggerPin, OUTPUT);
        pinMode(echoPin,    INPUT);
        return;
    }

    void sendTriggerPulse(void)
    {
    #ifdef DEBUG_ULTRASONIC
        printTimestamp();
        std::cout << "Sending trigger pulse for 10 microseconds\n";
    #endif // DEBUG_ULTRASONIC
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        return;
    }

    unsigned long getEchoPulseDuration(void)
    {
    #ifdef DEBUG_ULTRASONIC
        printTimestamp();
        std::cout << "Recieving echo pulse\n";
    #endif // DEBUG_ULTRASONIC
        return pulseIn(echoPin, HIGH);
    }

    double getDistance(DistanceType type = CENTIMETER)
    {
        sendTriggerPulse();
        long duration = getEchoPulseDuration();
        double dist = (double)duration / 2.0;
        
        switch (type)
        {
        case CENTIMETER:
        #ifdef DEBUG_ULTRASONIC
            printTimestamp();
            std::cout << "Calculate distance: " << dist << "\n";
        #endif // DEBUG_ULTRASONIC
            return dist;

        case INCH:
        #ifdef DEBUG_ULTRASONIC
            printTimestamp();
            std::cout << "Calculate distance: " << dist * 0.393701 << "\n";
        #endif // DEBUG_ULTRASONIC
            return dist * 0.393701;
        }
    }

    int inRange(double min, double max)
    {
        double distance = getDistance();

        if (distance >= min && distance <= max)
        {
        #ifdef DEBUG_ULTRASONIC
            printTimestamp();
            std::cout << "Distance is in range: " << distance << "\n";
        #endif // DEBUG_ULTRASONIC
            return TRUE;
        }
        return FALSE;
    }

private:
    const uint8_t triggerPin;
    const uint8_t echoPin;
};

#endif // _SUBSYSTEM_ULTRASONIC_cpp_