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

#ifndef _CORE_NAVIGATION_SLAM_C_
    #define _CORE_NAVIGATION_SLAM_C_

#include "SLAM.h"

#include <math.h>
#include <stdlib.h>

float32 distance(Vector3D* a, Vector3D* b)
{
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
}

SLAMState* SLAMInitialize(void)
{
    SLAMState* state = (SLAMState*)malloc(sizeof(SLAMState));

    state->position.x    = 0.0f;
    state->position.y    = 0.0f;
    state->position.z    = 0.0f;
    state->landmarks     = (Vector3D*)malloc(sizeof(Vector3D) * MAX_LANDMARKS);
    state->landmarkCount = 0;
    state->covariance    = (float32*)malloc(sizeof(float32) * MAX_LANDMARKS * 2);

    return state;
}

void SLAMUpdate(SLAMState* state, Vector3D* measurements, uint32 measurementsCount)
{
    // Prediction step
    state->covariance[0] += MOTION_NOISE;
    state->covariance[1] += MOTION_NOISE;

    // Update step for each measurement
    for(uint32 i = 0; i < measurementsCount; ++i)
    {
        float32 innovation = distance(&state->position, &measurements[i]);

        // Kalman gain calculation
        float32 K = state->covariance[0] / (state->covariance[0] + MEASUREMENT_NOISE);

        // State update
        state->position.x += K * (measurements[i].x - state->position.x);
        state->position.y += K * (measurements[i].y - state->position.y);
        state->position.z += K * (measurements[i].z - state->position.z);

        // Covariance update
        state->covariance[0] *= (1.0f - K);
    }
}

void SLAMAddLandmark(SLAMState* state, Vector3D landmark)
{
    if(state->landmarkCount >= MAX_LANDMARKS)
        return;

    state->landmarks[state->landmarkCount++] = landmark;
}

#endif // _CORE_NAVIGATION_SLAM_C_
