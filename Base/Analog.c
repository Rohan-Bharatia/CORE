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

#ifndef _CORE_BASE_ANALOG_C_
    #define _CORE_BASE_ANALOG_C_

#include "Analog.h"

void analogReference(uint8 mode)
{
    ADC_CONTROL = (ADC_CONTROL & 0x0F) | ((mode & 0x07) << 4);
}

int32 analogRead(uint8 pin)
{
    ADC_CONTROL = pin & 0x0F;
    while (ADC_CONTROL & 0x80); // Wait for conversion
    return ADC_DATA & 0xFFF;
}

void analogWrite(uint8 pin, int32 value)
{
    uint32 data = (pin << 16) | (value & 0xFFF);
    DAC_DATA    = data;
}

#endif // _CORE_BASE_ANALOG_C_
