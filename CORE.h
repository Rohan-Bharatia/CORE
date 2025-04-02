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

#pragma once

#ifndef _CORE_H_
    #define _CORE_H_

// Base files
#include "Base/Types.h"
#include "Base/Analog.h"
#include "Base/Digital.h"
#include "Base/Time.h"
#include "Base/Interrupts.h"
#include "Base/Mempool.h"
#include "Base/Serial.h"
#include "Base/I2C.h"
#include "Base/SPI.h"
#include "Base/CAN.h"
#include "Base/Server.h"

// Motor files
#include "Motor/Motor.h"
#include "Motor/DC.h"
#include "Motor/Servo.h"
#include "Motor/Stepper.h"
#include "Motor/BLDC.h"
#include "Motor/LinearActuator.h"

// Controller files
#include "Controller/Geometry.h"
#include "Controller/PID.h"
#include "Controller/StateMachine.h"
#include "Controller/KalmanFilter.h"
#include "Controller/Kinematics.h"
#include "Controller/Trajectory.h"

// Sensor files
#include "Sensor/Sensor.h"
#include "Sensor/IMU.h"
#include "Sensor/Encoder.h"
#include "Sensor/Distance.h"
#include "Sensor/Force.h"
#include "Sensor/Power.h"
#include "Sensor/Color.h"
#include "Sensor/GPS.h"

// Version macros
#define STRINGIFY(x) #x
#define CORE_MAKE_VERSION(major, minor, patch) STRINGIFY(major) "." STRINGIFY(minor) "." STRINGIFY(patch)
#define CORE_VERSION_MAJOR 1
#define CORE_VERSION_MINOR 0
#define CORE_VERSION_PATCH 0
#define CORE_VERSION_STR CORE_MAKE_VERSION(CORE_VERSION_MAJOR, CORE_VERSION_MINOR, CORE_VERSION_PATCH)

#endif // _CORE_H_
