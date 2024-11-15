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

#include <vector>
#include <cmath>
#include <iostream>

#include "prerequisites.c"
#include "control.c"
#include "base.c"

template<typename T = double>
class Bezier
{
public:
    Bezier(void) = default;
    Bezier(std::vector<Point<T>>& controlPoints) : controlPoints(controlPoints)
    {
        return;
    }

    Point<T> calculate(T t) const
    {
        if (controlPoints.empty())
            return Point<T>::ZERO;

    #ifdef DEBUG_BEZIER
        printTimestamp();
        std::cout << "Bezier curve calculated at " << t << " is " << deCasteljau(controlPoints, t) << "\n";
    #endif // DEBUG_BEZIER

        return deCasteljau(controlPoints, t);
    }

    std::vector<Point<T>> generate(uint16_t resolution = 100) const
    {
        std::vector<Point<T>> curve;

        for (int i = 0; i < resolution; ++i)
        {
            T t = (T)i / resolution;
            curve.push_back(controlPoints.empty() ? Point<T>::ZERO : deCasteljau(controlPoints, t));
        }

    #ifdef DEBUG_BEZIER
        printTimestamp();
        std::cout << "Bezier curve generated at a resolution of " << resolution << " is " << curve << "\n";
    #endif // DEBUG_BEZIER

        return curve;
    }

private:
    std::vector<Point> controlPoints;

    Point<T> deCasteljau(const std::vector<Point<T>>& points, T t) const
    {
        if (points.size() == 1)
            return points[0];

        std::vector<Point> next;

        for (int i = 0; i < points.size() - 1; ++i)
        {
            T x = (1 - t) * points[i].x + t * points[i + 1].x;
            T y = (1 - t) * points[i].y + t * points[i + 1].y;
            T z = (1 - t) * points[i].z + t * points[i + 1].z;

            next.emplace_back(Point{x, y, z});
        }
        
        return deCasteljau(next, t);
    }
};

#endif // _CONTROL_BEZIER_cpp_