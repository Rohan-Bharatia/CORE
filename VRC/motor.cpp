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

#ifndef _VRC_MOTOR_cpp_
    #define _VRC_MOTOR_cpp_

#include <iostream>
#include <cmath>

#include "prerequisites.c"
#include "driver.cpp"
#include "CORE.c"

namespace vrc
{
    class Motor
    {
    public:
        Motor(const uint8_t pin) : pin(pin)
        {
            return;
        }

        void setSpeed(int speed)
        {
            CLAMP(speed, -127, 127);
            uint8_t direction = (speed >= 0) ? 1 : 0; dir = direction;
            driver.write(pin, MOTOR_SPEED_SET, (direction << 7) | abs(speed));
        #ifdef DEBUG_SMART_MOTOR
            printTimestamp();
            std::cout << "Setting motor: " << pin << " speed to: " << speed << "\n";
        #endif // DEBUG_SMART_MOTOR
            return;
        }

        int getSpeed(void)
        {
            int response = driver.read(pin, MOTOR_SPEED_GET);
            if (response == -1)
                return -1;
            uint8_t direction = (response & 0x80) >> 7; dir = direction;
            uint8_t speed     = response & 0x7F;
        #ifdef DEBUG_SMART_MOTOR
            printTimestamp();
            std::cout << "Getting motor: " << pin << " speed: " << direction == 0 ? speed : -speed << "\n";
        #endif // DEBUG_SMART_MOTOR
            return direction == 0 ? speed : -speed;
        }

        void setDirection(int direction)
        {
        #ifdef DEBUG_SMART_MOTOR
            printTimestamp();
            std::cout << "Setting motor: " << pin << " direction to: " << direction << "\n";
        #endif // DEBUG_SMART_MOTOR
            dir = direction;
            setSpeed(getSpeed() * (direction == 0 ? -1 : 1));
            return;
        }

        void move(int voltage)
        {
        #ifdef DEBUG_SMART_MOTOR
            printTimestamp();
            std::cout << "Moving motor\n";
        #endif // DEBUG_SMART_MOTOR
            CLAMP(voltage, -127, 127);
            uint8_t low  = abs(voltage) & 0xFF;
            uint8_t high = (abs(voltage) >> 8) & 0xFF;
            driver.write(pin, MOTOR_MOVE, (dir << 7) | high, low);
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_SMART_MOTOR
            printTimestamp();
            std::cout << "Stopping motor\n";
        #endif // DEBUG_SMART_MOTOR
            driver.write(pin, MOTOR_STOP);
            return;
        }

    private:
        const uint8_t pin;
        int dir;
    };
} // namespace vrc

#endif // _VRC_MOTOR_cpp_