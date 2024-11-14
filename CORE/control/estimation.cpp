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
    class Kalman
    {
    public:
        Kalman(void) = default;
        Kalman(double process, double measurement, double error) : Q(process), R(measurement), P(error)
        {
            return;
        }

        void setInitialState(double is)
        {
            state = is;
        #ifdef DEBUG_ESTIMATION
            printTimestamp();
            std::cout << "Write state: " << state << "\n";
        #endif // DEBUG_ESTIMATION
            return;
        }

        double estimate(double measurement)
        {
            P      += Q;
            float K = P / (P + R);
            state  += K * (measurement - state);
            P      *= (1 - K);
        #ifdef DEBUG_ESTIMATION
            printTimestamp();
            std::cout << "Get estimation: " << state << "\n";
        #endif // DEBUG_ESTIMATION
            return state;
        }

    private:
        double Q, R, P;
        double state;
    };

    class Complimentary
    {
    public:
        Complimentary(void) = default;
        Complimentary(double alpha) : alpha(alpha), estimate(0.0)
        {
            return;
        }

        double update(std::vector<double> data, double dt)
        {
            if (data.size() <= 1)
                estimate += data[0];
            else
            {
                for (int i = 0; i < data.size() - 1; ++i)
                    estimate += alpha * (data[i] * dt) + (1.0 - alpha) * data[i + 1];
            }
        #ifdef DEBUG_ESTIMATION
            printTimestamp();
            std::cout << "Get estimate: " << estimate << "\n";
        #endif // DEBUG_ESTIMATION
            return estimate;
        }

    private:
        float alpha;
        float estimate;
    };
} // namespace filter

#endif // _CONTROL_PREREQUISITES_c_