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

#ifndef _CORE_BASE_SPI_C_
    #define _CORE_BASE_SPI_C_

#include "SPI.h"

void spiBegin(void)
{
    SPI_CONTROL = 0x50; // Enable SPI (master mode)
}

void spiEnd(void)
{
    SPI_CONTROL = 0x00;
}

void spiSetClockDivider(uint8 div)
{
    SPI_CONTROL = (SPI_CONTROL & 0xF0) | (div & 0x0F);
}

void spiSetBitOrder(uint8 bitOrder)
{
    if (bitOrder == LSBFIRST)
        SPI_CONTROL |= 0x08;
    else // MSBFIRST
        SPI_CONTROL &= ~0x80;
}

void spiSetDataMode(uint8 mode)
{
    switch (mode)
    {
    case SPI_MODE0:
        SPI_CONTROL &= ~0x30;
        return;
    case SPI_MODE1:
        SPI_CONTROL |= 0x10;
        return;
    case SPI_MODE2:
        SPI_CONTROL |= 0x20;
        return;
    case SPI_MODE3:
        SPI_CONTROL |= 0x30;
        return;
    default:
        SPI_CONTROL = 0x00;
        return;
    }
}

uint8 spiTransfer(uint8 data)
{
    SPI_DATA = data;
    while (!(SPI_DATA & 0x08));
    return SPI_DATA;
}

#endif // _CORE_BASE_SPI_C_
