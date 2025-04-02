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

#ifndef _CORE_SENSOR_COLOR_C_
    #define _CORE_SENSOR_COLOR_C_

#include "Color.h"

#include "../Base/I2C.h"
#include "../Base/Time.h"

static void begin(Color* color)
{
    i2cBegin();
    i2cSetClock(400000); // 400kHz I2C

    i2cBeginTransmission(color->address);
    i2cWrite(0x80); // Command register
    i2cWrite(0x03); // Power ON
    i2cEndTransmission(true);

    delay(2); // Wait for power up

    i2cBeginTransmission(color->address);
    i2cWrite(0x80 | 0x00); // Enable register
    i2cWrite(0x0B); // Enable RGBC and power
    i2cEndTransmission(true);
}

static void end(Color* color)
{
    i2cEnd();
}

static void update(Color* color)
{
    uint8 buffer[8];

    i2cBeginTransmission(color->address);
    i2cWrite(0x94); // RGBC data registers
    i2cEndTransmission(false);
    i2cRequestFrom(color->address, 8);

    for(int i = 0; i < 8; ++i)
        buffer[i] = i2cRead();

    color->clear = (buffer[1] << 8) | buffer[0];
    color->red   = (buffer[3] << 8) | buffer[2];
    color->green = (buffer[5] << 8) | buffer[4];
    color->blue  = (buffer[7] << 8) | buffer[6];
}

static bool isConnected(Color* color)
{
    i2cBeginTransmission(color->address);
    return i2cEndTransmission(false) == 0;
}

Color* colorInitialize(uint8 address)
{
    Color* color;

    color->base->begin       = (void(*)(void))begin;
    color->base->end         = (void(*)(void))end;
    color->base->update      = (void(*)(void))update;
    color->base->isConnected = (bool(*)(void))isConnected;
    color->address           = address;
    color->red               = 0;
    color->green             = 0;
    color->blue              = 0;
    color->clear             = 0;

    return color;
}

#endif // _CORE_SENSOR_COLOR_C_
