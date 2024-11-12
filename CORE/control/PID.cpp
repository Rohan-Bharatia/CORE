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

#ifndef _CONTROL_PID_cpp_
    #define _CONTROL_PID_cpp_

#include <algorithm>
#include <iostream>
#include <cmath>

#include "prerequisites.c"
#include "base.c"

enum PIDMode
{
    P_MODE,
    PI_MODE,
    PD_MODE,
    PID_MODE
}

struct PIDController
{
    double kP;
    double kI;
    double kD;
    double setpoint         = 0.0;
    double error            = 0.0;
    double integral         = 0.0;
    double min              = -100.0;
    double max              = 100.0;
    double last             = 0.0;
    PIDMode mode            = PID_MODE;
    double integralLimit    = std::abs(max);
    double maxROC           = 10.0;
    double derivativeFilter = 0.8;
};

class PID
{
public:
    PID(void) = default;
    PID(PIDController* pid) : pid(pid)
    {
        return;
    }

    void setSetpoint(double setpoint)
    {
        pid->setpoint = setpoint;
    #ifdef DEBUG_PID
        printTimestamp();
        std::cout << "Write setpoint: " << pid->setpoint << "\n";
    #endif // DEBUG_PID
        return;
    }

    void setMode(PIDMode mode)
    {
        pid->mode = mode;
    #ifdef DEBUG_PID
        printTimestamp();
        std::cout << "Write mode: " << pid->mode << "\n";
    #endif // DEBUG_PID
        return;
    }

    void setGains(double kP, double kI, double kD)
    {
        pid->kP = kP;
        pid->kI = kI;
        pid->kD = kD;
    #ifdef DEBUG_PID
        printTimestamp();
        std::cout << "Write proportional gain: " << pid->kP << "\n";
        printTimestamp();
        std::cout << "Write integral gain: " << pid->kI << "\n";
        printTimestamp();
        std::cout << "Write derivative gain: " << pid->kD << "\n";
    #endif // DEBUG_PID
        return;
    }

    void setLimits(double min, double max, double integral = pid->integralLimit, double ROC = pid->maxROC)
    {
    #ifdef DEBUG_PID
        printTimestamp();
        std::cout << "Write minimum output: " << pid->min << "\n";
        printTimestamp();
        std::cout << "Write maximum output: " << pid->max << "\n";

        if (integral != pid->integralLimit)
        {
            printTimestamp();
            std::cout << "Write integral limit: " << pid->integralLimit << "\n";
        }

        if (ROC != pid->maxROC)
        {
            printTimestamp();
            std::cout << "Write rate of change maximum: " << pid->integralLimit << "\n";
        }
    #endif // DEBUG_PID
        pid->min           = min;
        pid->max           = max;
        pid->integralLimit = std::abs(integral);
        pid->maxROC        = ROC;
        return;
    }

    double compute(double process, double dt)
    {
        double error      = pid->setpoint - process;
        double outP       = pid->kP * error;
        pid->integral    += error * dt;
        pid->integral     = std::clamp(pid->integral, pid->integralLimit, -pid->integralLimit);
        double outI       = pid->kI * pid->integral;
        double derivative = (error - pid->error) / dt;
        double outD       = pid->kD * (derivative * pid->derivativeFilter);
        pid->error        = error;
        double result;

        switch (pid->mode)
        {
        case P_MODE:
            result = outP;
            break;
        
        case PI_MODE:
            result = outP + outI;
            break;

        case PD_MODE:
            result = outP + outD;
            break;

        case PID_MODE:
            result = outPID;
            break;

        default:
            result = 0.0;
            break;
        }

        result    = std::clamp(result, pid->min, pid->max);
        result    = rate(result, pid->last, pid->maxROC);
        pid->last = result;

    #ifdef DEBUG_PID
        printTimestamp();
        std::cout << "PID set to " << pid->kP << ", " << pid->kI << ", " << pid->kD << " calculates to " << result << "\n";
    #endif // DEBUG_PID
        return result;
    }

private:
    PIDController* pid;

    double rate(double output, double last, float max)
    {
        double delta = output - last;
        if (std::abs(delta) > max)
            return last + std::copysign(max, delta);
        return output;
    }
};

#endif // _CONTROL_PID_cpp_
