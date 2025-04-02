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

#ifndef _CORE_NAVIGATION_SLAM_H_
    #define _CORE_NAVIGATION_SLAM_H_

#include "../Base/Types.h"
#include "../Controller/Geometry.h"

#define MAX_LANDMARKS     100
#define MEASUREMENT_NOISE 0.1f
#define MOTION_NOISE      0.2f

typedef struct
{
    Vector3D position;
    Vector3D* landmarks;
    uint32 landmarkCount;
    float32* covariance;
} SLAMState;

SLAMState* SLAMInitialize(void);
void SLAMUpdate(SLAMState* state, Vector3D* measurements, uint32 measurementsCount);
void SLAMAddLandmark(SLAMState* state, Vector3D landmark);

#endif // _CORE_NAVIGATION_SLAM_H_
