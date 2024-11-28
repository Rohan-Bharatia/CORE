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

#ifndef _SUBSYSTEM_IMU_cpp_
    #define _SUBSYSTEM_IMU_cpp_

#include <cmath>
#include <iostream>

#include "prerequisites.c"
#include "control.c"
#include "base.c"

#define TIME_STEP 0.01

class IMU
{
public:
    IMU(void) = default;
    IMU(const uint8_t gyroPin, const uint8_t accelPin) : gyroPin(gyroPin), accelPin(accelPin)
    {
        pinMode(gyroPin, INPUT);
        pinMode(accelPin, INPUT);
        
        g *= analogRead(gyroPin);
        a *= analogRead(accelPin);
        return;
    }

    void reset(void)
    {
    #ifdef DEBUG_IMU
        printTimestamp(void);
        std::cout << "Reseting IMU\n";
    #endif // DEBUG_IMU
        velocity = PointD::ZERO;
        pos      = PointD::ZERO;
    }

    double getPitch(void) const
    {
        double p = atan2(a.y, sqrt(a.x * a.x + a.z * a.z)) * (180 / PI);
    #ifdef DEBUG_IMU
        printTimestamp(void);
        std::cout << "Reading IMU pitch: " << p << "\n";
    #endif // DEBUG_IMU
        return p;
    }

    double getYaw(void) const
    {
        double y = g.z * TIME_STEP;
    #ifdef DEBUG_IMU
        printTimestamp(void);
        std::cout << "Reading IMU yaw: " << y << "\n";
    #endif // DEBUG_IMU
        return y;
    }

    double getRoll(void) const
    {
        double r = atan2(a.x, sqrt(a.y * a.y + a.z * a.z)) * (180 / PI);
    #ifdef DEBUG_IMU
        printTimestamp(void);
        std::cout << "Reading IMU roll: " << r << "\n";
    #endif // DEBUG_IMU
        return r;
    }

    PointD getPosition(void) const
    {
        velocity += (a * TIME_STEP);
        pos       = velocity * TIME_STEP;

    #ifdef DEBUG_IMU
        printTimestamp(void);
        std::cout << "Reading IMU position: " << pos << "\n";
    #endif // DEBUG_IMU
        return pos;
    }

private:
    const uint8_t gyroPin;
    const uint8_t accelPin;
    PointD g;
    PointD a;
    PointD velocity
    PointD pos;
};

#endif // _SUBSYSTEM_IMU_cpp_
