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

#ifndef _CORE_CONTROLLERS_LINEAR_ACTUATOR_H_
    #define _CORE_CONTROLLERS_LINEAR_ACTUATOR_H_

#include "Motor.h"
#include "../Base/Digital.h"
#include "../Base/Analog.h"

typedef struct
{
    Motor* base;
    uint8 pwmPin;
    uint8 dirPin;
    uint8 limitSwitchPin;
    uint32 maxPosition;
    uint32 currentPosition;
} LinearActuator;

LinearActuator* linearActuatorInitialize(uint8 pwmPin, uint8 dirPin, uint8 limitSwitchPin);
void LinearActuatorSetPosition(LinearActuator* actuator, uint32 position);

#endif // _CORE_CONTROLLERS_LINEAR_ACTUATOR_H_
