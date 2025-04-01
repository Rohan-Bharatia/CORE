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

#ifndef _CORE_CONTROLLERS_LINEAR_ACTUATOR_C_
    #define _CORE_CONTROLLERS_LINEAR_ACTUATOR_C_

#include "LinearActuator.h"

static void begin(LinearActuator* actuator)
{
    pinMode(actuator->pwmPin, OUTPUT);
    pinMode(actuator->dirPin, OUTPUT);
    pinMode(actuator->limitSwitchPin, INPUT_PULLUP);
    actuator->currentPosition = 0;
}

static void end(LinearActuator* actuator)
{
    digitalWrite(actuator->pwmPin, LOW);
    digitalWrite(actuator->dirPin, LOW);
}

static void setSpeed(LinearActuator* actuator, int32 speed)
{
    if(speed == 0)
    {
        analogWrite(actuator->pwmPin, 0);
        return;
    }

    digitalWrite(actuator->dirPin, speed > 0);
    analogWrite(actuator->pwmPin, speed > 0 ? speed : speed * -1);
}

static void stop(LinearActuator* actuator)
{
    setSpeed(actuator, 0);
}

LinearActuator* initializeLinearActuator(uint8 pwmPin, uint8 dirPin, uint8 limitSwitchPin)
{
    LinearActuator* actuator;

    actuator->base->begin     = (void(*)(void))begin;
    actuator->base->end       = (void(*)(void))end;
    actuator->base->setSpeed  = (void(*)(int32))setSpeed;
    actuator->base->stop      = (void(*)(void))stop;
    actuator->pwmPin          = pwmPin;
    actuator->dirPin          = dirPin;
    actuator->limitSwitchPin  = limitSwitchPin;
    actuator->maxPosition     = 1000;
    actuator->currentPosition = 0;

    return actuator;
}

void setLinearActuatorPosition(LinearActuator* actuator, uint32 position)
{
    if(position > actuator->maxPosition)
        position = actuator->maxPosition;

    int32 error = position - actuator->currentPosition;
    setSpeed((LinearActuator*)actuator, error > 0 ? 255 : -255);
    actuator->currentPosition = position;
}

#endif // _CORE_CONTROLLERS_LINEAR_ACTUATOR_C_
