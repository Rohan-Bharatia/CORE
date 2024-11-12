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

#ifndef _CONTROL_SIGNAL_CONDITION_cpp_
    #define _CONTROL_SIGNAL_CONDITION_cpp_

#include <cmath>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

namespace SignalCondition
{
    double lowPassFilter(double input, double previous, double alpha)
    {
        double result =  alpha * input + (1.0 - alpha) * previous;
    
    #ifdef DEBUG_SIGNAL_CONDITION
        printTimestamp();
        std::cout << "Low pass filter on: " << input << " is " << result << "\n";
    #endif // DEBUG_SIGNAL_CONDITION

        return result;
    }

    double lowPassFilter(double input, double previousIn, double previousOut, double alpha)
    {
        double result =  alpha * (previousOut + input - previousIn);
    
    #ifdef DEBUG_SIGNAL_CONDITION
        printTimestamp();
        std::cout << "High pass filter on: " << input << " is " << result << "\n";
    #endif // DEBUG_SIGNAL_CONDITION

        return result;
    }

    double movingAverage(double value, double* window, uint32_t size, int& index)
    {
        window[index] = value;
        index         = (index + 1) % size;
        double sum    = 0.0;

        for (int i = 0; i < size; ++i)
            sum += window[i];

        return sum / size;
    }

    double applyDeadband(double input, double threshold)
    {
    #ifdef DEBUG_SIGNAL_CONDITION
        printTimestamp();
        std::cout << "Deadband on: " << input << " with a threshold of " << threshold << "\n";
    #endif // DEBUG_SIGNAL_CONDITION

        if (std::abs(input) < threshold)
            return 0.0;
        
        return input;
    }
} // namespace SignalCondition

#endif // _CONTROL_SIGNAL_CONDITION_cpp_