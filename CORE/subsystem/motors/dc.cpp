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

#ifndef _SUBSYSTEM_DC_MOTOR_cpp_
    #define _SUBSYSTEM_DC_MOTOR_cpp_

#include <algorithm>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

namespace motor
{
    class DC
    {
    public:
        DC(void) = default;
        DC(const uint8_t pin) : pin(pin)
        {
            pinMode(pin, OUTPUT);
            return;
        }

        void setSpeed(double speed) : speed(std::clamp(speed, 0, 255))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Write DC motor speed: " << speed << "\n";
        #endif // DEBUG_MOTOR
            return;
        }
        void setDirection(int8_t direction) : direction(std::clamp(direction, -1, 1))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Write DC motor direction: " << (direction > 0 ? "right\n" : "left\n");
        #endif // DEBUG_MOTOR
            return;
        }

        void spin(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Spinning DC motor\n";
        #endif // DEBUG_MOTOR
            speed *= direction;
            digitalWrite(pin, (int)speed);
            return;
        }

        void spinfor (const unsigned long ms)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Spinning DC motor for: " << ms / 1000 << " seconds\n";
        #endif // DEBUG_MOTOR
            spin(void);
            delay(ms);
            stop(void);
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Stopping DC motor\n";
        #endif // DEBUG_MOTOR
            analogWrite(pin, 0);
            return;
        }

    private:
        const uint8_t pin;
        double speed;
        int8_t direction;
    };
} // namespace motor

#endif // _SUBSYSTEM_DC_MOTOR_cpp_