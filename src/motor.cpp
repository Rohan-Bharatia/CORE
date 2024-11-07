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

#ifndef _CORE_MOTOR_c_
    #define _CORE_MOTOR_c_

#include "int.c"
#include "gpio.cpp"

// Motor types, currently, DC and Servo motors only
enum motorType { DC, SERVO };

// PWM specifics
#define PWM_MIN_PULSE_WIDTH 1000 // 1 ms in microseconds (min degrees)
#define PWM_MAX_PULSE_WIDTH 2000 // 2 ms in microseconds (max degrees)
#define PWM_FREQUENCY       50   // Typical servo frequency in Hz

// DC motor directions
#define LEFT -1
#define RIGHT 1

// Motor class - template class for motor type
template<motorType T>
class Motor
{
public:
    // Class constructor
    Motor(uint32 port) : port(port)
    {
        // Get motor type defime
        switch(T)
        {
        case DC:
            #define DC_MOTOR
            return;

        case SERVO:
            #define SERVO_MOTOR
            return;
        }
    }

#ifdef DC_MOTOR
    // Spins a DC motor at a speed in a direction
    void spin(uint32 speed, int8 direction)
    {
        if (ignore)
            GPIO::write(port, speed * ((-1 <= direction <= 1 ? direction : 0)));
        return;
    }

    // // Spins a DC motor at a speed in a direction for a duration of time (in ms)
    void spinFor(uint32 speed, int8 direction, uint32 duration)
    {
        if (ignore)
        {
            GPIO::write(port, speed * ((-1 <= direction <= 1 ? direction : 0)));
            delay(duration);
        }
        return;
    }
#endif // DC_MOTOR
#ifdef SERVO_MOTOR
    // Sets the degree bounds for a servo motor
    void setBounds(uint16 min, uint16 max) : min(min), max(max)
    {}

    // Sets the position of a servo motor in degrees
    void set(double degrees)
    {
        if (ignore)
            GPIO::write(port, PWM_MIN_PULSE_WIDTH + ((min <= degrees <= max ? degrees : (min + max) / 2) / 180f) * (PWM_MAX_PULSE_WIDTH - PWM_MIN_PULSE_WIDTH));
        return;
    }
#endif // SERVO_MOTOR

    // Halts a motor
    void stop(void)
    {
        ignore = true;
        GPIO::write(port, 0);
        ignore = false;
        return;
    }

private:
    uint32 port;
    bool ignore = false;
    int min, max;
};

#endif // _CORE_MOTOR_c_
