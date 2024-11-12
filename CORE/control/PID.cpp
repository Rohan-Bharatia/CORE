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

#ifndef _ROBOTICS_PID_cpp_
    #define _ROBOTICS_PID_cpp_

#include <algorithm>

struct PIDController
{
    double kP;
    double kI;
    double kD;
    double setpoint = (double)0.0;
    double error    = (double)0.0;
    double integral = (double)0.0;
    double min      = (double)-100.0;
    double max      = (double) 100.0;
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
        return;
    }

    void setGains(double kP, double kI, double kD)
    {
        pid->kP = kP;
        pid->kI = kI;
        pid->kD = kD;
        return;
    }

    double compute(double process, double dt)
    {
        double error      = pid->setpoint - process;
        double outP       = pid->kP * error;
        pid->integral    += error * dt;
        double outI       = pid->kI * pid->integral;
        double derivative = (error - pid->error) / dt;
        double outD       = pid->kD * derivative;
        double output     = outP + outI + outD;
        pid->error        = error;

        return std::clamp(output, pid->min, pid->max);
    }

private:
    PIDController* pid;
};

#endif // _ROBOTICS_PID_cpp_
