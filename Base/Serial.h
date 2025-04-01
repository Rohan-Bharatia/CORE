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

#ifndef _CORE_BASE_SERIAL_H_
    #define _CORE_BASE_SERIAL_H_

#include "Types.h"

#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_6N2 0x07

#define F_CPU        16000000L
#define UART_BASE    0x40000000
#define UART_DATA    (*(volatile uint8*)(UART_BASE + 0))
#define UART_STATUS  (*(volatile uint8*)(UART_BASE + 1))
#define UART_CONTROL (*(volatile uint8*)(UART_BASE + 2))
#define UART_BAUD    (*(volatile uint32*)(UART_BASE + 3))

void serialBegin(uint32 baudRate);
void serialEnd(void);
int32 serialAvailable(void);
int32 serialRead(void);
opsize serialWrite(uint8 bytes);
opsize serialPrint(const char* str);
void serialFlush(void);

#endif // _CORE_BASE_SERIAL_H_
