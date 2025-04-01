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

#ifndef _CORE_BASE_I2C_H_
    #define _CORE_BASE_I2C_H_

#include "Types.h"

#define I2C_BASE    0x40001000
#define I2C_CONTROL (*(volatile uint8*)(I2C_BASE + 0))
#define I2C_STATUS  (*(volatile uint8*)(I2C_BASE + 1))
#define I2C_DATA    (*(volatile uint8*)(I2C_BASE + 2))
#define I2C_CLOCK   (*(volatile uint32*)(I2C_BASE + 3))

void i2cBegin(void);
void i2cEnd(void);
void i2cSetClock(uint32 clockFreq);
uint8 i2cRequestFrom(uint8 address, uint8 quantity);
void i2cBeginTransmission(uint8 address);
uint8 i2cEndTransmission(bool sendStop);
opsize i2cWrite(uint8 data);
int32 i2cRead(void);
int32 i2cAvailable(void);

#endif // _CORE_BASE_I2C_H_
