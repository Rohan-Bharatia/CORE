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

#ifndef _SUBSYSTEM_SERVO_MOTOR_cpp_
    #define _SUBSYSTEM_SERVO_MOTOR_cpp_

#include <algorithm>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

namespace motor
{
    class Servo
    {
    public:
        Servo(void) = default;
        Servo(const uint8_t enablePin, const uint8_t pwmPin) enablePin(enablePin), pwmPin(pwmPin)
        {
            pinMode(enablePin,      OUTPUT);
            pinMode(pwmPin,         OUTPUT);
            digitalWrite(enablePin, HIGH);
            return;
        }
        
        void setBounds(uint16_t min, uint16_t max) : min(min), max(max)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Setting servo motor bounds: { " << min << ", " << max << " }\n";
        #endif // DEBUG_MOTOR
            return;
        }

        void angle(double degs)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Going to angle on servo motor: " << degrees << "°\n";
        #endif // DEBUG_MOTOR
            angle = std::clamp(angle, min, max);
            analogWrite(pwmPin, MAP(speed, 0, 180, 0, 255));
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp(void);
            std::cout << "Stopping servo motor\n";
        #endif // DEBUG_MOTOR
            analogWrite(enablePin, 0);
            return;
        }

    private:
        const uint8_t enablePin;
        const uint8_t pwmPin;
        uint16_t min = 0, max = 180;
    };
} // namespace motor

#endif // _SUBSYSTEM_SERVO_MOTOR_cpp_