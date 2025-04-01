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

#ifndef _CORE_CONTROLLER_KALMAN_FILTER_H_
    #define _CORE_CONTROLLER_KALMAN_FILTER_H_

#include "../Base/Types.h"

typedef struct
{
    float32 state;        // State estimate
    float32 variance;     // Estimate variance
    float32 processNoise; // Process noise
    float32 sensorNoise;  // Sensor noise
} KalmanFilter;

KalmanFilter* KalmanFilterInit(float32 state, float32 variance);
float32 KalmanFilterUpdate(KalmanFilter* filter, float32 measurement);

#endif // _CORE_CONTROLLER_KALMAN_FILTER_H_
