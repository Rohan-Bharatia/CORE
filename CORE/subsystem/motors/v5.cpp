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

        void setSpeed(int speed) : speed(CLAMP(speed, -127, 127))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Write v5 smart motor speed: " << speed << "\n";
        #endif // DEBUG_MOTOR
            return;
        }

        void setDirection(int8_t direction) : direction(CLAMP(direction, LEFT, RIGHT))
        {
            #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Write DC motor direction: " << (direction > 0 ? "right\n" : "left\n");
        #endif // DEBUG_MOTOR
        }

        void spin(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Spinning v5 smart motor\n";
        #endif // DEBUG_MOTOR
            speed *= direction;
            sendCommand(0x01, speed);
            return;
        }

        void stop(int hardStop = FALSE)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Stopping v5 smart motor\n";
        #endif // DEBUG_MOTOR
            int s = hardStop ? -readFeedback(void) : 0;
            sendCommand(0x01, s);
            return;
        }

    private:
        HardwareSerial& serial = HardwareSerial(2, 1);
        const uint8_t port;
        int speed;
        int8_t direction;

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