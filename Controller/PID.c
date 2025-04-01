#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#pragma once

#ifndef _CORE_CONTROLLER_PID_C_
    #define _CORE_CONTROLLER_PID_C_

#include "PID.h"

#include "../Base/Time.h"

PIDController* PIDInitialize(float32 kp, float32 ki, float32 kd)
{
    PIDController* pid;

    pid->kp        = kp;
    pid->ki        = ki;
    pid->kd        = kd;
    pid->setpoint  = 0;
    pid->lastError = 0;
    pid->integral  = 0;
    pid->lastTime  = millis();

    return pid;
}

void PIDSetTarget(PIDController* pid, float32 setpoint)
{
    pid->setpoint = setpoint;
}

float32 PIDCompute(PIDController* pid, float32 currentValue)
{
    uint32 now        = millis();
    float32 deltaTime = (now - pid->lastTime) / 1000.0f;

    float32 error      = pid->setpoint - currentValue;
    pid->integral     += error * deltaTime;
    float32 derivative = (error - pid->lastError) / deltaTime;
    float32 output     = (pid->kp * error) +
                       (pid->ki * pid->integral) +
                       (pid->kd * derivative);

    pid->lastError = error;
    pid->lastTime  = now;

    return output;
}

void PIDReset(PIDController* pid)
{
    pid->lastError = 0;
    pid->integral  = 0;
    pid->lastTime  = millis();
}

#endif // _CORE_CONTROLLER_PID_C_
