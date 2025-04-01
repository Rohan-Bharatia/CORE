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

#ifndef _CORE_BASE_CAN_C_
    #define _CORE_BASE_CAN_C_

#include "CAN.h"

void canBegin(uint32 baudRate)
{
    CAN_CONTROL = baudRate | 0x80000000; // Enable CAN
}

void canEnd(void)
{
    CAN_CONTROL = 0;
}

bool canSend(CANMessage* msg)
{
    // Check if TX buffer is available
    if (!(CAN_STATUS & 0x04))
    {
        CAN_TX_DATA = (msg->id << 21) | (msg->length << 16) | msg->data[0];
        return true;
    }
    return false;
}

bool canReceive(CANMessage* msg)
{
    // Check if message received
    if (CAN_STATUS & 0x01)
    {
        uint32 rxData = CAN_RX_DATA;
        msg->id       = (rxData >> 21) & 0x7FF;
        msg->length   = (rxData >> 16) & 0x0F;
        msg->data[0]  = rxData & 0xFF;
        return true;
    }
    return false;
}

uint8 canAvailable(void)
{
    return CAN_STATUS & 0x01;
}

#endif // _CORE_BASE_CAN_C_
