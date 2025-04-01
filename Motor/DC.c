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

#ifndef _CORE_CONTROLLERS_DC_C_
    #define _CORE_CONTROLLERS_DC_C_

#include "DC.h"

static void begin(DCMotor* motor)
{
    pinMode(motor->enable, OUTPUT);
    pinMode(motor->in1, OUTPUT);
    pinMode(motor->in2, OUTPUT);
}

static void end(DCMotor* motor)
{
    digitalWrite(motor->enable, LOW);
    digitalWrite(motor->in1, LOW);
    digitalWrite(motor->in2, LOW);
}

static void setSpeed(DCMotor* motor, int32 speed)
{
    if (speed > 0)
    {
        digitalWrite(motor->in1, HIGH);
        digitalWrite(motor->in2, LOW);
    } else if (speed < 0)
    {
        digitalWrite(motor->in1, LOW);
        digitalWrite(motor->in2, HIGH);
        speed = -speed;
    } else
    {
        digitalWrite(motor->in1, LOW);
        digitalWrite(motor->in2, LOW);
    }
    analogWrite(motor->enable, speed);
}

static void stop(DCMotor* motor)
{
    setSpeed(motor, 0);
}

DCMotor* initializeDCMotor(uint8 enable, uint8 in1, uint8 in2)
{
    DCMotor* motor;

    motor->base->begin    = (void(*)(void))begin;
    motor->base->end      = (void(*)(void))end;
    motor->base->setSpeed = (void(*)(int32))setSpeed;
    motor->base->stop     = (void(*)(void))stop;
    motor->enable         = enable;
    motor->in1            = in1;
    motor->in2            = in2;

    return motor;
}

#endif // _CORE_CONTROLLERS_DC_C_
