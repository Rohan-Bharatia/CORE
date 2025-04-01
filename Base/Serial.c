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

#ifndef _CORE_BASE_SERIAL_C_
    #define _CORE_BASE_SERIAL_C_

#include "Serial.h"

void serialBegin(uint32 baudRate)
{
    UART_BAUD    = (F_CPU / 16 / baudRate - 1);
    UART_CONTROL = 0x018; // Enable RX & TX
}

void serialEnd(void)
{
    UART_CONTROL = 0x00;
}

int32 serialAvailable(void)
{
    return UART_STATUS & 0x80;
}

int32 serialRead(void)
{
    while (!serialAvailable());
    return UART_DATA;
}

opsize serialWrite(uint8 bytes)
{
    while (!(UART_STATUS & 0x20));
    UART_DATA = bytes;
    return 1;
}

opsize serialPrint(const char* str)
{
    opsize count = 0;
    while (*str)
    {
        count += serialWrite(*str++);
        ++count;
    }
    return count;
}

void serialFlush(void)
{
    while (serialAvailable())
        serialRead();
}

#endif // _CORE_BASE_SERIAL_C_
