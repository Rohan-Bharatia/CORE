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

#ifndef _CORE_BASE_SPI_H_
    #define _CORE_BASE_SPI_H_

#include "Types.h"

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define LSBFIRST 0
#define MSBFIRST 1

#define SPI_BASE    0x40002000
#define SPI_CONTROL (*(volatile uint8*)(SPI_BASE + 0))
#define SPI_STATUS  (*(volatile uint8*)(SPI_BASE + 1))
#define SPI_DATA    (*(volatile uint8*)(SPI_BASE + 2))

void spiBegin(void);
void spiEnd(void);
void spiSetClockDivider(uint8 div);
void spiSetBitOrder(uint8 bitOrder);
void spiSetDataMode(uint8 mode);
uint8 spiTransfer(uint8 data);

#endif // _CORE_BASE_SPI_H_
