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

#include "BLDC.h"

// Six-step commutation sequence
static const uint8 COMMUTATION_TABLE[6][6] =
{
    {1, 0, 0, 1, 0, 0}, // Phase A-B
    {1, 0, 0, 0, 0, 1}, // Phase A-C
    {0, 0, 1, 0, 0, 1}, // Phase B-C
    {0, 1, 1, 0, 0, 0}, // Phase B-A
    {0, 1, 0, 0, 1, 0}, // Phase C-A
    {0, 0, 0, 1, 1, 0}  // Phase C-B
};

static void begin(BLDCMotor* motor)
{
    for(int i = 0; i < 2; ++i)
    {
        pinMode(motor->phaseA[i], OUTPUT);
        pinMode(motor->phaseB[i], OUTPUT);
        pinMode(motor->phaseC[i], OUTPUT);
    }
}

static void end(BLDCMotor* motor)
{
    for(int i = 0; i < 2; ++i)
    {
        digitalWrite(motor->phaseA[i], LOW);
        digitalWrite(motor->phaseB[i], LOW);
        digitalWrite(motor->phaseC[i], LOW);
    }
}

static void setSpeed(BLDCMotor* motor, int32 speed)
{
    if(speed == 0)
    {
        digitalWrite(motor->phaseA[0], 0);
        digitalWrite(motor->phaseA[1], 0);
        digitalWrite(motor->phaseB[0], 0);
        digitalWrite(motor->phaseB[1], 0);
        digitalWrite(motor->phaseC[0], 0);
        digitalWrite(motor->phaseC[1], 0);
        return;
    }

    // Update commutation
    motor->commutationStep = (motor->commutationStep + 1) % 6;

    // Apply commutation pattern
    digitalWrite(motor->phaseA[0], COMMUTATION_TABLE[motor->commutationStep][0]);
    digitalWrite(motor->phaseA[1], COMMUTATION_TABLE[motor->commutationStep][1]);
    digitalWrite(motor->phaseB[0], COMMUTATION_TABLE[motor->commutationStep][2]);
    digitalWrite(motor->phaseB[1], COMMUTATION_TABLE[motor->commutationStep][3]);
    digitalWrite(motor->phaseC[0], COMMUTATION_TABLE[motor->commutationStep][4]);
    digitalWrite(motor->phaseC[1], COMMUTATION_TABLE[motor->commutationStep][5]);
}

static void stop(BLDCMotor* motor)
{
    setSpeed(motor, 0);
}

BLDCMotor* initializeDCMotor(uint8 phaseAHigh, uint8 phaseALow,
                             uint8 phaseBHigh, uint8 phaseBLow,
                             uint8 phaseCHigh, uint8 phaseCLow)
{
    BLDCMotor* motor;

    motor->base->begin    = (void(*)(void))begin;
    motor->base->end      = (void(*)(void))end;
    motor->base->setSpeed = (void(*)(int32))setSpeed;
    motor->base->stop     = (void(*)(void))stop;
    motor->phaseA[0]      = phaseAHigh;
    motor->phaseA[1]      = phaseALow;
    motor->phaseB[0]      = phaseBHigh;
    motor->phaseB[1]      = phaseBLow;
    motor->phaseC[0]      = phaseCHigh;
    motor->phaseC[1]      = phaseCLow;

    return motor;
}

#endif // _CORE_CONTROLLERS_DC_C_
