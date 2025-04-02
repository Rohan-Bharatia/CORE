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

#ifndef _CORE_SENSOR_GPS_C_
    #define _CORE_SENSOR_GPS_C_

#include "GPS.h"

#include "../Base/Serial.h"

#include <stdlib.h>

static void parseGPGGA(GPS* gps, const char* sentence)
{
    char* ptr   = (char*)sentence;
    uint8 field = 0;

    while (*ptr)
    {
        if (*ptr == ',')
        {
            field++;
            switch(field)
            {
                case 2: // Latitude
                    gps->data->latitude = atof(ptr + 1);
                    break;
                case 4: // Longitude
                    gps->data->longitude = atof(ptr + 1);
                    break;
                case 6: // Fix quality
                    gps->data->fix = *(ptr + 1) - '0';
                    break;
                case 7: // Satellites
                    gps->data->satellites = atoi(ptr + 1);
                    break;
                case 9: // Altitude
                    gps->data->altitude = atof(ptr + 1);
                    break;
            }
        }
        ptr++;
    }
}

static void parseGPRMC(GPS* gps, const char* sentence)
{
    char* ptr = (char*)sentence;
    uint8 field = 0;

    while (*ptr)
    {
        if (*ptr == ',')
        {
            field++;
            switch(field)
            {
                case 1: // Time
                    gps->data->timestamp = atol(ptr + 1);
                    break;
                case 7: // Speed
                    gps->data->speed = atof(ptr + 1) * 1.852; // Knots -> km/h
                    break;
                case 8: // Course
                    gps->data->course = atof(ptr + 1);
                    break;
            }
        }
        ptr++;
    }
}

static void begin(GPS* gps)
{
    SerialBegin(gps->serialPort, 9600); // Standard NMEA baud rate
    gps->bufferIndex = 0;
}

static void end(GPS* gps)
{
    SerialEnd();
}

static void update(GPS* gps)
{
    while (serialAvailable())
    {
        char c = serialRead();

        if (c == '\n')
        {
            gps->buffer[gps->bufferIndex] = '\0';

            if (strstr(gps->buffer, "$GPGGA"))
                parseGPGGA(gps, gps->buffer);
            else if (strstr(gps->buffer, "$GPRMC"))
                parseGPRMC(gps, gps->buffer);

            gps->bufferIndex = 0;
        }
        else if (gps->bufferIndex < 127)
            gps->buffer[gps->bufferIndex++] = c;
    }
}

static bool isConnected(GPS* gps)
{
    return true;
}

GPS* GPSInitialize(uint8 serialPort)
{
    GPS* gps;

    gps->base->begin       = (void(*)(void))begin;
    gps->base->end         = (void(*)(void))end;
    gps->base->update      = (void(*)(void))update;
    gps->base->isConnected = (bool(*)(void))isConnected;
    gps->serialPort        = serialPort;
    gps->data->latitude    = 0.0f;
    gps->data->longitude   = 0.0f;
    gps->data->altitude    = 0.0f;
    gps->data->speed       = 0.0f;
    gps->data->course      = 0.0f;
    gps->data->satellites  = 0;
    gps->data->fix         = 0;
    gps->data->timestamp   = 0;
    gps->bufferIndex       = 0;

    return gps;
}

#endif // _CORE_SENSOR_GPS_C_
