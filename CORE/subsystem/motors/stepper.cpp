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

#ifndef _SUBSYSTEM_STEPPER_MOTOR_cpp_
    #define _SUBSYSTEM_STEPPER_MOTOR_cpp_

#include <algorithm>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

namespace motor
{
    class Stepper
    {
    public:
        Stepper(void) = default;
        Stepper(const uint8_t enablePin, const uint8_t stepPin, const uint8_t dirPin, int maxSteps) : 
            enablePin(enablePin), stepPin(stepPin), dirPin(dirPin), maxSteps(maxSteps)
        {
            pinMode(enablePin,      OUTPUT);
            pinMode(stepPin,        OUTPUT);
            pinMode(dirPin,         OUTPUT);
            digitalWrite(enablePin, HIGH);
            return;
        }

        void setSpeed(double steps) : sps(std::clamp(steps, 1, 1000))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Write stepper motor speed (steps): " << steps << "\n";
        #endif // DEBUG_MOTOR
            return;
        }
        void setDirection(int direction)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Write stepper motor direction: " (direction > 0 ? "right\n" : "left\n");
        #endif // DEBUG_MOTOR
            digitalWrite(dirPin, direction > 0 ? HIGH, LOW);
        }

        void step(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Stepping stepper motor\n";
        #endif // DEBUG_MOTOR
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1000000 / sps);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(1000000 / sps);
            return;
        }

        void angle(double degrees)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Going to angle on stepper motor: " << degrees << "°\n";
        #endif // DEBUG_MOTOR
            spinfor (degrees / (360 / maxSteps));
        }

        void stepfor (uint64_t steps)
        {
            for (int i = 0; i < steps; ++i)
                step();
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Stepping stepper motor: " << steps << " times\n";
        #endif // DEBUG_MOTOR
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Stopping stepper motor\n";
        #endif // DEBUG_MOTOR
            digitalWrite(enablePin, LOW);
            return;
        }

    private:
        const uint8_t enablePin;
        const uint8_t stepPin;
        const uint8_t dirPin;
        int maxSteps;
        const int sps = 100;
    };
} // namespace motor

#endif // _SUBSYSTEM_STEPPER_MOTOR_cpp_