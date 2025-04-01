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

#ifndef _CORE_BASE_CAN_H_
    #define _CORE_BASE_CAN_H_

#include "Types.h"

#define CAN_BASE    0x40003000
#define CAN_CONTROL (*(volatile uint32*)(CAN_BASE + 0))
#define CAN_STATUS  (*(volatile uint32*)(CAN_BASE + 4))
#define CAN_TX_DATA (*(volatile uint32*)(CAN_BASE + 8))
#define CAN_RX_DATA (*(volatile uint32*)(CAN_BASE + 12))

typedef struct
{
    uint32 id;
    uint8 length;
    uint8 data[8];
} CANMessage;

void canBegin(uint32 baudRate);
void canEnd(void);
bool canSend(CANMessage* msg);
bool canReceive(CANMessage* msg);
uint8 canAvailable(void);

#endif // _CORE_BASE_CAN_H_
