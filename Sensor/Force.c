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

#ifndef _CORE_SENSOR_FORCE_C_
    #define _CORE_SENSOR_FORCE_C_

#include "Force.h"

#include "../Base/I2C.h"

static void begin(ForceTorque* ft)
{
    i2cBegin();
    i2cSetClock(100000); // 100kHz I2C

    i2cBeginTransmission(ft->address);
    i2cWrite(0x00); // Reset
    i2cEndTransmission(true);
}

static void end(ForceTorque* ft)
{
    i2cEnd();
}

static void update(ForceTorque* ft)
{
    uint8 buffer[24];

    i2cBeginTransmission(ft->address);
    i2cWrite(0x01); // Data register
    i2cEndTransmission(false);
    i2cRequestFrom(ft->address, 24);

    for(int i = 0; i < 24; ++i)
        buffer[i] = i2cRead();

    // Convert raw data to physical values
    ft->force.x  = *((float32*)&buffer[0]);
    ft->force.y  = *((float32*)&buffer[4]);
    ft->force.z  = *((float32*)&buffer[8]);
    ft->torque.x = *((float32*)&buffer[12]);
    ft->torque.y = *((float32*)&buffer[16]);
    ft->torque.z = *((float32*)&buffer[20]);
}

static bool isConnected(ForceTorque* ft)
{
    i2cBeginTransmission(ft->address);
    return i2cEndTransmission(false) == 0;
}

ForceTorque* forceTorqueInitialize(uint8 address)
{
    ForceTorque* ft;

    ft->base->begin       = (void(*)(void))begin;
    ft->base->end         = (void(*)(void))end;
    ft->base->update      = (void(*)(void))update;
    ft->base->isConnected = (bool(*)(void))isConnected;
    ft->address           = address;
    ft->force.x           = 0.0f;
    ft->force.y           = 0.0f;
    ft->force.z           = 0.0f;
    ft->torque.x          = 0.0f;
    ft->torque.y          = 0.0f;
    ft->torque.z          = 0.0f;

    return ft;
}

#endif // _CORE_SENSOR_FORCE_C_
