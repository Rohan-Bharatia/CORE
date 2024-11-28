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

#ifndef _CONTROL_PREREQUISITES_c_
    #define _CONTROL_PREREQUISITES_c_

#include <vector>

#include "prerequisites.c"
#include "base.c"

namespace filter
{
    double kalman(double Q, double R, double P, double state, double measurement)
    {
        P      += Q;
        float K = P / (P + R);
        state  += K * (measurement - state);
        P      *= (1 - K);
    #ifdef DEBUG_ESTIMATION
        printTimestamp(void);
        std::cout << "Get kalman estimation: " << state << "\n";
    #endif // DEBUG_ESTIMATION
        return state;
    }

    double complimentary(double alpha, std::vector<double> data, double dt)
    {
        double estimate = 0.0;
        if (data.size(void) <= 1)
            estimate += data[0];
        else
        {
            for (int i = 0; i < data.size(void) - 1; ++i)
                estimate += alpha * (data[i] * dt) + (1.0 - alpha) * data[i + 1];
        }
    #ifdef DEBUG_ESTIMATION
        printTimestamp(void);
        std::cout << "Get complimentary estimation: " << estimate << "\n";
    #endif // DEBUG_ESTIMATION
        return estimate;
    }
} // namespace filter

#endif // _CONTROL_PREREQUISITES_c_