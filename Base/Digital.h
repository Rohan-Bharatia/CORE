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

#ifndef _CORE_BASE_DIGITAL_H_
    #define _CORE_BASE_DIGITAL_H_

#include "Types.h"

// Pin modes
#define INPUT             0
#define OUTPUT            1
#define INPUT_PULLUP      2
#define INPUT_PULLDOWN    3
#define OUTPUT_OPEN_DRAIN 4

// Pin states
#define LOW  0
#define HIGH 1

#define GPIO_BASE 0x40000000
#define GPIO_MODE (*(volatile uint32*)(GPIO_BASE + 0))
#define GPIO_OUT  (*(volatile uint32*)(GPIO_BASE + 4))
#define GPIO_IN   (*(volatile uint32*)(GPIO_BASE + 8))

void pinMode(uint8 pin, uint8 mode);
void digitalWrite(uint8 pin, uint8 value);
int32 digitalRead(uint8 pin);
void digitalToggle(uint8 pin);

#endif // _CORE_BASE_DIGITAL_H_
