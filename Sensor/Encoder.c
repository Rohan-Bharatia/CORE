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

#ifndef _CORE_SENSOR_ENCODER_C_
    #define _CORE_SENSOR_ENCODER_C_

#include "Encoder.h"

#include "../Base/Digital.h"

static void begin(Encoder* encoder)
{
    pinMode(encoder->pinA, INPUT_PULLUP);
    pinMode(encoder->pinB, INPUT_PULLUP);
    encoder->position = 0;
}

static void end(Encoder* encoder)
{
    pinMode(encoder->pinA, INPUT);
    pinMode(encoder->pinB, INPUT);
}

static void update(Encoder* encoder)
{
    static uint8 lastState = 0;
    uint8 state            = (digitalRead(encoder->pinA) << 1) | digitalRead(encoder->pinB);

    switch(state | (lastState << 2))
    {
        case 0b0001: // Forward
        case 0b0111:
        case 0b1110:
        case 0b1000:
            ++encoder->position;
            break;
        case 0b0100: // Reverse
        case 0b0010:
        case 0b1011:
        case 0b1101:
            --encoder->position;
            break;
    }

    lastState = state;
}

static bool isConnected(Encoder* encoder)
{
    return true;
}

Encoder* encoderInitialize(uint8 pinA, uint8 pinB, uint16 ppr)
{
    Encoder* encoder;

    encoder->base->begin       = (void(*)(void))begin;
    encoder->base->end         = (void(*)(void))end;
    encoder->base->update      = (void(*)(void))update;
    encoder->base->isConnected = (bool(*)(void))isConnected;
    encoder->pinA              = pinA;
    encoder->pinB              = pinB;
    encoder->ppr               = ppr;
    encoder->position          = 0;

    return encoder;
}

float32 encoderGetRotation(Encoder* encoder)
{
    return (encoder->position * 360.0f) / encoder->ppr;
}

void encoderReset(Encoder* encoder)
{
    encoder->position = 0;
}

#endif // _CORE_SENSOR_ENCODER_C_
