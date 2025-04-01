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

#ifndef _CORE_BASE_SERVER_C_
    #define _CORE_BASE_SERVER_C_

#include "Server.h"

static uint8 macAddress[6]       = { 0 };
static NetworkClient clients[32] = { NULL };
static uint8 numClients          = 0;

bool networkBegin(IPAddress* ip)
{
    if (!ip)
        return false;

    ETH_CONTROL = 0x01; // Enable network interface
    return true;
}

void networkEnd(void)
{
    ETH_CONTROL = 0x00;
}

NetworkClient* networkConnect(IPAddress* ip, uint16 port)
{
    if (!ip || numClients >= 32)
        return NULL;

    NetworkClient* client = &clients[numClients++];
    client->ip            = *ip;
    client->port          = port;

    return client;
}

NetworkServer* networkListen(uint16 port, uint8 maxClients)
{
    static NetworkServer server;
    server.port       = port;
    server.maxClients = maxClients;

    ETH_CONTROL |= 0x02; // Enable listening mode

    return &server;
}

opsize networkSend(NetworkClient* client, const uint8* data, opsize length)
{
    if (!client || !data)
        return 0;

    // Simulate sending data
    return length;
}

opsize networkReceive(NetworkClient* client, uint8* buffer, opsize maxLength)
{
    if (!client || !buffer)
        return 0;

    // Data available
    if (ETH_STATUS & 0x04)
        return maxLength > 0; // Simulate receiving 1 byte
    return 0;
}

void networkClose(NetworkClient* client)
{
    if (!client)
        return;

    for (int i = 0; i < numClients; ++i)
    {
        if (&clients[i] == client)
        {
            // Move remaining clients up
            for (int j = i; j < numClients - 1; j++)
                clients[j] = clients[j + 1];
            --numClients;
            break;
        }
    }
}

#endif // _CORE_BASE_SERVER_C_
