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

#ifndef _CONTROL_BEZIER_cpp_
    #define _CONTROL_BEZIER_cpp_

#include <algorithm>
#include <iostream>
#include <vector>

#include "prerequisites.c"
#include "point.cpp"
#include "base.c"

template<typename T = double>
class Trajectory
{
public:
    Trajectory(void) = default;
    Trajectory(T maxVelocity, T maxAcceleration, Point<T> start, Point<T> end) : maxVelocity(maxVelocity), maxAcceleration(maxAcceleration),
                                                                                 start(start), end(end), current(start), currentVelocity((T)0.0)
    {
        return;
    }

    Point<T> calculate(T dt) const
    {
        Point<T> distance  = end - current;
        T direction = (distance > 0) ? (T)1.0 : (T)-1.0;

        if ((direction * currentVelocity) < maxVelocity)
        {
            currentVelocity += direction * maxAcceleration * dt;
            currentVelocity  = std::clamp(currentVelocity, -maxVelocity, maxVelocity);
        }

        current += currentVelocity * dt;

        if (direction * (end - current) <- 0)
        {
            current         = end;
            currentVelocity = (T)0.0;
        }

    #ifdef DEBUG_BEZIER
        printTimestamp();
        std::cout << "Bezier curve calculated at " << dt << " is " << current << "\n";
    #endif // DEBUG_BEZIER

        return current;
    }

    std::vector<Point<T>> generate(uint16_t resolution = 100) const
    {
        std::vector<Point<T>> traj;

        for (int i = 0; i < resolution; ++i)
        {
            T t = (T)i / resolution;
            traj.push_back((start == end) ? Point<T>::ZERO : calculate(t));
        }

    #ifdef DEBUG_TRAJECTORY
        printTimestamp();
        std::cout << "Trajectory generated at a resolution of " << resolution << " is " << traj << "\n";
    #endif // DEBUG_TRAJECTORY

        return traj;
    }

private:
    T maxVelocity, maxAcceleration;
    Point<T> start, end, current;
    T currentVelocity;
};

#endif // _CONTROL_BEZIER_cpp_