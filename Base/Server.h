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

#ifndef _CORE_BASE_SERVER_H_
    #define _CORE_BASE_SERVER_H_

#include "Types.h"

#define ETH_BASE     0x40004000
#define ETH_CONTROL  (*(volatile uint32*)(ETH_BASE + 0))
#define ETH_STATUS   (*(volatile uint32*)(ETH_BASE + 4))
#define ETH_MAC_HIGH (*(volatile uint32*)(ETH_BASE + 8))
#define ETH_MAC_LOW  (*(volatile uint32*)(ETH_BASE + 12))

typedef struct
{
    uint8 octets[4];
} IPAddress;

typedef struct
{
    uint16 port;
    IPAddress ip;
} NetworkClient;

typedef struct
{
    uint16 port;
    uint8 maxClients;
} NetworkServer;

bool networkBegin(IPAddress* ip);
void networkEnd(void);
NetworkClient* networkConnect(IPAddress* ip, uint16 port);
NetworkServer* networkListen(uint16 port, uint8 maxClients);
opsize networkSend(NetworkClient* client, const uint8* data, opsize length);
opsize networkReceive(NetworkClient* client, uint8* buffer, opsize maxLength);
void networkClose(NetworkClient* client);

#endif // _CORE_BASE_SERVER_H_
