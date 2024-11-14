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

#include "prerequisites.c"
#include "base.c"

#define TIME_STEP 0.01

class IMU
{
public:
    IMU(void) = default;
    IMU(double gyro, double accel) : gyro(gyro), accel(accel)
    {
        g *= gyro;
        a *= accel;
    }

    void reset(void)
    {
    #ifdef DEBUG_IMU
        printTimestamp();
        std::cout << "Reseting IMU\n";
    #endif // DEBUG_IMU
        velocity = PointD(0, 0, 0);
        pos      = PointD(0, 0, 0);
    }

    double getPitch(void) const
    {
        double p = atan2(ay, sqrt(a.x * a.x + a.z * a.z)) * (180 / PI);
    #ifdef DEBUG_IMU
        printTimestamp();
        std::cout << "Reading IMU pitch: " << p << "\n";
    #endif // DEBUG_IMU
        return p;
    }

    double getYaw(void) const
    {
        double y = g.z * TIME_STEP;
    #ifdef DEBUG_IMU
        printTimestamp();
        std::cout << "Reading IMU yaw: " << y << "\n";
    #endif // DEBUG_IMU
        return y;
    }

    double getRoll(void) const
    {
        double r = atan2(ax, sqrt(a.y * a.y + a.z * a.z)) * (180 / PI);
    #ifdef DEBUG_IMU
        printTimestamp();
        std::cout << "Reading IMU roll: " << r << "\n";
    #endif // DEBUG_IMU
        return r;
    }

    PointD getPosition(void) const
    {
        velocity += (a * TIME_STEP);
        pos       = velocity * TIME_STEP;

    #ifdef DEBUG_IMU
        printTimestamp();
        std::cout << "Reading IMU position: " << pos << "\n";
    #endif // DEBUG_IMU
        return pos;
    }

private:
    double gyro, accel;
    PointD g, a;
    PointD velocity, pos;
};

#endif // _SUBSYSTEM_IMU_cpp_