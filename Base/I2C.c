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

#ifndef _CORE_BASE_I2C_C_
    #define _CORE_BASE_I2C_C_

#include "I2C.h"

static uint8 rxBuffer[32] = { 0 };
static uint8 rxIndex      = 0;
static uint8 rxLength     = 0;

void i2cBegin(void)
{
    I2C_CONTROL = 0x80; // Enable I2C
}

void i2cEnd(void)
{
    I2C_CONTROL = 0x00;
}

void i2cSetClock(uint32 clockFreq)
{
    I2C_CLOCK = clockFreq;
}

uint8 i2cRequestFrom(uint8 address, uint8 quantity)
{
    I2C_CONTROL = 0x80 | 0x20; // Start condition
    I2C_DATA    = (address << 1) | 1; // Address + read bit

    rxLength = quantity;
    rxIndex  = 0;

    for (uint8 i = 0; i < quantity; ++i)
    {
        while (!(I2C_STATUS & 0x80)); // Wait for completion
        rxBuffer[i] = I2C_DATA;
    }

    return quantity;
}

void i2cBeginTransmission(uint8 address)
{
    I2C_CONTROL = 0x80 | 0x20; // Start condition
    I2C_DATA    = (address << 1); // Address + write bit
}

uint8 i2cEndTransmission(bool sendStop)
{
    if (sendStop)
        I2C_CONTROL = 0x80 | 0x10; // Stop condition
    return 0;
}

opsize i2cWrite(uint8 data)
{
    I2C_DATA = data;
    while (!(I2C_STATUS & 0x80)); // Wait for completion
    return 1;
}

int32 i2cRead(void)
{
    if (rxIndex < rxLength)
        return rxBuffer[rxIndex++];
    return -1;
}

int32 i2cAvailable(void)
{
    return rxLength - rxIndex;
}

#endif // _CORE_BASE_I2C_C_
