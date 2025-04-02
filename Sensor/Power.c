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

#ifndef _CORE_SENSOR_FORCE_C_
    #define _CORE_SENSOR_FORCE_C_

#include "Power.h"

#include "../Base/Analog.h"
#include "../Base/Digital.h"

static void begin(Power* power)
{
    pinMode(power->voltagePin, INPUT);
    pinMode(power->currentPin, INPUT);
}

static void end(Power* power)
{
    pinMode(power->voltagePin, INPUT);
    pinMode(power->currentPin, INPUT);
}

static void update(Power* power)
{
    power->voltage = analogRead(power->voltagePin) * ((power->maxVoltage - power->minVoltage) / 1023.0f) * 5.0f; // *5 for voltage divider
    power->current = analogRead(power->currentPin) * ((power->maxVoltage - power->minVoltage) / 1023.0f) / 0.1f; // 0.1 ohm shunt
    power->power   = power->voltage * power->current;
}

static bool isConnected(Power* power)
{
    return true;
}

Power* powerInitialize(uint8 voltagePin, uint8 currentPin, uint32 min, uint32 max)
{
    Power* power;

    power->base->begin       = (void(*)(void))begin;
    power->base->end         = (void(*)(void))end;
    power->base->update      = (void(*)(void))update;
    power->base->isConnected = (bool(*)(void))isConnected;
    power->voltagePin        = voltagePin;
    power->currentPin        = currentPin;
    power->minVoltage        = min;
    power->maxVoltage        = max;
    power->voltage           = 0;
    power->current           = 0;
    power->power             = 0;

    return power;
}

#endif // _CORE_SENSOR_FORCE_C_
