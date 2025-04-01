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

#ifndef _CORE_BASE_DIGITAL_C_
    #define _CORE_BASE_DIGITAL_C_

#include "Digital.h"

void pinMode(uint8 pin, uint8 mode)
{
    uint32 shift = pin * 2;
    GPIO_MODE   &= ~(0x03 << shift);
    GPIO_MODE   |= (mode & 0x03) << shift;
}

void digitalWrite(uint8 pin, uint8 value)
{
    if (value)
        GPIO_OUT |= (1 << pin);
    else
        GPIO_OUT &= ~(1 << pin);
}

int32 digitalRead(uint8 pin)
{
    return (GPIO_IN & (1 << pin)) != 0;
}

void digitalToggle(uint8 pin)
{
    GPIO_OUT ^= (1 << pin);
}

#endif // _CORE_BASE_DIGITAL_C_
