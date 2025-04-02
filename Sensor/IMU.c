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

#ifndef _CORE_SENSOR_IMU_C_
    #define _CORE_SENSOR_IMU_C_

#include "IMU.h"

#include "../Base/I2C.h"

static void begin(IMU* imu)
{
    i2cBegin();
    i2cSetClock(400000); // 400kHz I2C

    // Configure IMU registers
    i2cBeginTransmission(imu->address);
    i2cWrite(0x6B); // PWR_MGMT_1
    i2cWrite(0x00); // Wake up
    i2cEndTransmission(true);
}

static void end(IMU* imu)
{
    i2cEnd();
}

static void update(IMU* imu)
{
    uint8 buffer[14];

    i2cBeginTransmission(imu->address);
    i2cWrite(0x3B); // ACCEL_XOUT_H
    i2cEndTransmission(false);
    i2cRequestFrom(imu->address, 14);

    for(int i = 0; i < 14; i++)
        buffer[i] = i2cRead();

    // Convert raw data to physical values
    imu->accelerometer.x = (float32)((buffer[0] << 8) | buffer[1]) / 16384.0f;
    imu->accelerometer.y = (float32)((buffer[2] << 8) | buffer[3]) / 16384.0f;
    imu->accelerometer.z = (float32)((buffer[4] << 8) | buffer[5]) / 16384.0f;

    imu->gyroscope.x = (float32)((buffer[8] << 8) | buffer[9]) / 131.0f;
    imu->gyroscope.y = (float32)((buffer[10] << 8) | buffer[11]) / 131.0f;
    imu->gyroscope.z = (float32)((buffer[12] << 8) | buffer[13]) / 131.0f;

    imu->temperature = (float32)((buffer[6] << 8) | buffer[7]) / 340.0f + 36.53f;
}

static bool isConnected(IMU* imu)
{
    i2cBeginTransmission(imu->address);
    return i2cEndTransmission(false) == 0;
}

IMU* IMUInitialize(uint8 address)
{
    IMU* sensor;

    sensor->base->begin       = (void(*)(void))begin;
    sensor->base->update      = (void(*)(void))update;
    sensor->base->end         = (void(*)(void))end;
    sensor->base->isConnected = (bool(*)(void))isConnected;
    sensor->address           = address;
    sensor->accelerometer.x   = 0.0f;
    sensor->accelerometer.y   = 0.0f;
    sensor->accelerometer.z   = 0.0f;
    sensor->gyroscope.x       = 0.0f;
    sensor->gyroscope.y       = 0.0f;
    sensor->gyroscope.z       = 0.0f;
    sensor->magnetometer.x    = 0.0f;
    sensor->magnetometer.y    = 0.0f;
    sensor->magnetometer.z    = 0.0f;
    sensor->temperature       = 0.0f;

    return sensor;
}

#endif // _CORE_SENSOR_IMU_C_
