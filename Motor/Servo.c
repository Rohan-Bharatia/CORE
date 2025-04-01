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

#ifndef _CORE_CONTROLLERS_SERVO_C_
    #define _CORE_CONTROLLERS_SERVO_C_

#include "Servo.h"

#include "../Base/Time.h"

static void begin(ServoMotor* motor)
{
    pinMode(motor->pin, OUTPUT);

    motor->minPulse     = 544;  // 0 degrees
    motor->maxPulse     = 2400; // 180 degrees
    motor->currentAngle = 90;

    setServoAngle(motor, motor->currentAngle);
}

static void end(ServoMotor* motor)
{
    digitalWrite(motor->pin, LOW);
}

static void setSpeed(ServoMotor* motor, int32 speed)
{
    (void)speed;
}

static void stop(ServoMotor* motor)
{
    setSpeed(motor, 0);
}

ServoMotor* initializeServoMotor(uint8 pin)
{
    ServoMotor* motor;

    motor->base->begin    = (void(*)(void))begin;
    motor->base->end      = (void(*)(void))stop;
    motor->base->setSpeed = (void(*)(int32))setSpeed;
    motor->base->stop     = (void(*)(void))stop;
    motor->pin            = pin;

    return motor;
}

void setServoAngle(ServoMotor* motor, int32 angle)
{
    if (angle < 0)
        angle = 0;
    if (angle > 180)
        angle = 180;

    motor->currentAngle = angle;
    uint16 pulseWidth   = motor->minPulse + (angle * (motor->maxPulse - motor->minPulse) / 180);

    // Generate PWM pulse
    digitalWrite(motor->pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(motor->pin, LOW);
}

#endif // _CORE_CONTROLLERS_SERVO_C_
