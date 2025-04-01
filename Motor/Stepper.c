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

#ifndef _CORE_CONTROLLERS_STEPPER_C_
    #define _CORE_CONTROLLERS_STEPPER_C_

#include "Stepper.h"
#include "../Base/Time.h"

static const uint8 STEP_SEQUENCE[8][4] =
{
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

static void begin(StepperMotor* motor)
{
    pinMode(motor->pin1, OUTPUT);
    pinMode(motor->pin2, OUTPUT);
    pinMode(motor->pin3, OUTPUT);
    pinMode(motor->pin4, OUTPUT);
}

static void end(StepperMotor* motor)
{
    digitalWrite(motor->pin1, LOW);
    digitalWrite(motor->pin2, LOW);
    digitalWrite(motor->pin3, LOW);
    digitalWrite(motor->pin4, LOW);
}

static void setSpeed(StepperMotor* motor, int32 speed)
{
    if (speed == 0) return;
    motor->stepDelay = 1000000 / ((speed > 0 ? speed : speed * -1) * motor->stepsPerRev / 60);
}

static void stop(StepperMotor* motor)
{
    setSpeed(motor, 0);
}

StepperMotor* stepperInitialize(uint8 pin1, uint8 pin2, uint8 pin3, uint8 pin4, uint16 stepsPerRev)
{
    StepperMotor* motor;

    motor->base->begin    = (void(*)(void))begin;
    motor->base->end      = (void(*)(void))end;
    motor->base->setSpeed = (void(*)(int32))setSpeed;
    motor->base->stop     = (void(*)(void))stop;
    motor->pin1           = pin1;
    motor->pin2           = pin2;
    motor->pin3           = pin3;
    motor->pin4           = pin4;
    motor->stepsPerRev    = stepsPerRev;
    motor->stepDelay      = 2000;
    motor->currentStep    = 0;

    return motor;
}

void stepperSetPosition(StepperMotor* motor, int32 steps)
{
    int8 direction = (steps > 0 ? 1 : -1);
    steps          = (steps > 0 ? steps : steps * -1);

    for (int32 i = 0; i < steps; ++i)
    {
        motor->currentStep = (motor->currentStep + direction + 8) % 8;

        digitalWrite(motor->pin1, STEP_SEQUENCE[motor->currentStep][0]);
        digitalWrite(motor->pin2, STEP_SEQUENCE[motor->currentStep][1]);
        digitalWrite(motor->pin3, STEP_SEQUENCE[motor->currentStep][2]);
        digitalWrite(motor->pin4, STEP_SEQUENCE[motor->currentStep][3]);

        delayMicroseconds(motor->stepDelay);
    }
}

#endif // _CORE_CONTROLLERS_STEPPER_C_
