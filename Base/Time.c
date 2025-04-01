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

#ifndef _CORE_BASE_TIME_C_
    #define _CORE_BASE_TIME_C_

#include "Time.h"

void delay(uint32 ms)
{
    uint32 start = TIMER_COUNT;
    uint32 ticks = ms * 1000; // Convert to microseconds
    while ((TIMER_COUNT - start) < ticks);
}

void delayMicroseconds(uint32 us)
{
    uint32 start = TIMER_COUNT;
    while ((TIMER_COUNT - start) < us);
}

uint32 millis(void)
{
    return TIMER_COUNT / 1000;
}

uint32 micros(void)
{
    return TIMER_COUNT;
}

#endif // _CORE_BASE_TIME_C_
