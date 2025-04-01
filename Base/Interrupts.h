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

#ifndef _CORE_BASE_INTERRUPTS_H_
    #define _CORE_BASE_INTERRUPTS_H_

#include "Types.h"

typedef void (*InterruptHandler)(void);

#define MAX_INTERRUPTS 32

// Interrupt modes
#define INT_RISING  0x01
#define INT_FALLING 0x02
#define INT_CHANGE  0x03
#define INT_LOW     0x04
#define INT_HIGH    0x05

void attachInterrupt(uint8 pin, InterruptHandler handler, uint8 mode);
void detachInterrupt(uint8 pin);
void noInterrupts(void);
void interrupts(void);

#endif // _CORE_BASE_INTERRUPTS_H_
