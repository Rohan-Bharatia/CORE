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

#ifndef _SUBSYSTEM_MOTOR_cpp_
    #define _SUBSYSTEM_MOTOR_cpp_

#include <algorithm>
#include <iostream>

#include "prerequisites.c"
#include "base.c"

#define LEFT -1
#define RIGHT 1

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

        void speed(double speed) : speed(std::clamp(speed, 0, 255))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Write DC motor speed: " << speed << "\n";
        #endif // DEBUG_MOTOR
            return;
        }
        void direction(int8_t direction) : direction(std::clamp(direction, -1, 1))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Write DC motor direction: " << (direction > 0 ? "right\n" : "left\n");
        #endif // DEBUG_MOTOR
            return;
        }

        void spin(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Spinning DC motor\n";
        #endif // DEBUG_MOTOR
            speed *= direction;
            digitalWrite(pin, (int)speed);
            return;
        }

        void spinFor(const unsigned long ms)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Spinning DC motor for: " << ms / 1000 << " seconds\n";
        #endif // DEBUG_MOTOR
            spin();
            delay(ms);
            stop();
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
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

    class Servo
    {
    public:
        Servo(void) = default;
        Servo(const uint8_t enablePin, const uint8_t pwmPin) enablePin(enablePin), pwmPin(pwmPin)
        {
            pinMode(enablePin, OUTPUT);
            pinMode(pwmPin, OUTPUT);
            digitalWrite(enablePin, HIGH);
            return;
        }
        
        void setBounds(uint16_t min, uint16_t max) : min(min), max(max)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Setting servo motor bounds: { " << min << ", " << max << " }\n";
        #endif // DEBUG_MOTOR
            return;
        }

        void angle(double degs)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Going to angle on servo motor: " << degrees << "°\n";
        #endif // DEBUG_MOTOR
            angle = std::clamp(angle, min, max);
            analogWrite(pwmPin, MAP(speed, 0, 180, 0, 255));
            return;
        }

        void stop(void)
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
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

    class Stepper
    {
    public:
        Stepper(void) = default;
        Stepper(const uint8_t enablePin, const uint8_t stepPin, const uint8_t dirPin, int maxSteps) : 
            enablePin(enablePin), stepPin(stepPin), dirPin(dirPin), maxSteps(maxSteps)
        {
            pinMode(enablePin, OUTPUT);
            pinMode(stepPin, OUTPUT);
            pinMode(dirPin, OUTPUT);
            digitalWrite(enablePin, HIGH);
            return;
        }

        void speed(double steps) : sps(std::clamp(steps, 1, 1000))
        {
        #ifdef DEBUG_MOTOR
            printTimestamp();
            std::cout << "Write stepper motor speed (steps): " << steps << "\n";
        #endif // DEBUG_MOTOR
            return;
        }
        void direction(int direction)
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
            spinFor(degrees / (360 / maxSteps));
        }

        void stepFor(uint64_t steps)
        {
            for(int i = 0; i < steps; ++i)
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

#endif // _SUBSYSTEM_MOTOR_cpp_