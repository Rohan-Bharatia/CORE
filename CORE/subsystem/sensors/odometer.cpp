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

#ifndef _SUBSYSTEM_ODOMETER_cpp_
    #define _SUBSYSTEM_ODOMETER_cpp_

#include <vector>
#include <iostream>

#include "prerequisites.c"
#include "motors/dc.cpp"
#include "motors/stepper.cpp"
#include "control.c"
#include "base.c"

struct Pose
{
    PointD position;
    double theta;
};

class Odometry
{
public:
    Odometry(void) = default;
    Odometry(const uint8_t parallelPin, const uint8_t perpendicularPin, double radius, double ticksPerRev) :
        parallelPin(parallelPin), perpendicularPin(perpendicularPin), radius(radius), ticksPerRev(ticksPerRev)
    {
        pinMode(parallelPin,      INPUT);
        pinMode(perpendicularPin, INPUT);
        previous = { 0, 0 };
        return;
    }

    void setPose(PointD position, double theta)
    {
    #ifdef DEBUG_ODOMETER
        printTimestamp();
        std::cout << "Write pose: " << Pose{ position, theta } << "\n";
    #endif // DEBUG_ODOMETER
        current->position = position;
        current->theta    = theta;
        return;
    }

    Pose getPose(void)
    {
        double ticks[2]      = { analogRead(parallelPin), analogRead(perpendicularPin) };
        double delta[2]      = { ticks[0] - previous[0], ticks[1] - previous[1] };
        previous             = ticks;
        double distance[2]   = { (delta[0] / ticksPerRev) * (TAU * radius), (delta[1] / ticksPerRev) * (TAU * radius) };
        current->position.x += distance[0] * cos(current->theta) - distance[1] * sin(current->theta);
        current->position.y += distance[0] * sin(current->theta) + distance[1] * cos(current->theta);
        current->theta      += distance[1] / radius;
        if(theta > TAU)
            theta -= TAU;
        if(theta < 0)
            theta += TAU;
    #ifdef DEBUG_ODOMETER
        printTimestamp();
        std::cout << "Read pose: " << current << "\n";
    #endif // DEBUG_ODOMETER
        return current;
    }

private:
    const uint8_t parallelPin;
    const uint8_t perpendicularPin;
    double radius;
    double ticksPerRev;
    double[2] previous;
    Pose current = { PointD::ZERO, 0.0 };
};

#endif // _SUBSYSTEM_ODOMETER_cpp_