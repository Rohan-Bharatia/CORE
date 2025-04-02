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

#ifndef _CORE_SENSOR_DISTANCE_C_
    #define _CORE_SENSOR_DISTANCE_C_

#include "Distance.h"

#include "../Base/Digital.h"
#include "../Base/Time.h"

static void begin(Ultrasonic* ultrasonic)
{
    pinMode(ultrasonic->trigger, OUTPUT);
    pinMode(ultrasonic->echo, INPUT);
    digitalWrite(ultrasonic->trigger, LOW);
}

static void end(Ultrasonic* ultrasonic)
{
    digitalWrite(ultrasonic->trigger, LOW);
}

static void update(Ultrasonic* ultrasonic)
{
    digitalWrite(ultrasonic->trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic->trigger, LOW);

    ultrasonic->distance = pulseIn(ultrasonic->echo, HIGH) * SOUND_SPEED / 2;
}

static bool isConnected(Ultrasonic* ultrasonic)
{
    return true;
}

Ultrasonic* ultrasonicInitialize(uint8 trigger, uint8 echo)
{
    Ultrasonic* ultrasonic;

    ultrasonic->base->begin       = (void(*)(void))begin;
    ultrasonic->base->end         = (void(*)(void))end;
    ultrasonic->base->update      = (void(*)(void))update;
    ultrasonic->base->isConnected = (bool(*)(void))isConnected;
    ultrasonic->trigger           = trigger;
    ultrasonic->echo              = echo;
    ultrasonic->distance          = 0;

    return ultrasonic;
}

#endif // _CORE_SENSOR_DISTANCE_C_
