#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                               ...
//                  Copyright (C) 2024 Rohan Bharatia

#pragma endregion LICENSE

#pragma once

#ifndef _SUBSYSTEM_V5_MOTOR_cpp_
    #define _SUBSYSTEM_V5_MOTOR_cpp_

#include "prerequisites.c"
#include "base.c"

namespace motor
{
    class v5
    {
    public:
        v5(const uint8_t port) : port(port)
        {
            serial.begin(11520);
            return;
        }

        void setSpeed(int speed)
        {
            sendCommand(0x01, CLAMP(speed, -127, 127));
            return;
        }

        void stop(int hardStop = FALSE)
        {
            int s = hardStop ? -readFeedback(void) : 0;
            sendCommand(0x01, s);
            return;
        }

    private:
        HardwareSerial& serial = HardwareSerial(2, 1);
        const uint8_t port;

        void sendCommand(uint8_t command, uint8_t value)
        {
            const uint8_t packet[4] = { 0xAA, port, command, value };
            serial.write(packet, sizeof(packet));
            return;
        }

        int readFeedback(void)
        {
            if (serial.available(void))
            {
                uint8_t buffer[8];
                int bytesRead = serial.readBytes(buffer, sizeof(buffer));

                if (bytesRead > 0)
                {
                    int feedback = buffer[1];
                    return feedback;
                }
            }
            return -1;
        }
    };
} // namespace motor

#endif // _SUBSYSTEM_V5_MOTOR_cpp_