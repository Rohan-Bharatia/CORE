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

#ifndef _CORE_CONTROLLER_TRAJECTORY_C_
    #define _CORE_CONTROLLER_TRAJECTORY_C_

#include "Trajectory.h"

TrajectoryGenerator* trajectoryInit(Vector3D* start, Vector3D* end, float32 duration)
{
    TrajectoryGenerator* tg;

    tg->start       = *start;
    tg->end         = *end;
    tg->duration    = duration;
    tg->currentTime = 0.0f;

    return tg;
}

void trajectoryUpdate(TrajectoryGenerator* tg, float32 dt, Vector3D* position, Vector3D* velocity)
{
    if(tg->currentTime >= tg->duration)
    {
        *position   = tg->end;
        velocity->x = velocity->y = velocity->z = 0.0f;
        return;
    }

    float t  = tg->currentTime / tg->duration;
    float t2 = t * t;
    float t3 = t2 * t;

    // Cubic spline interpolation
    float h0 = 2 * t3 - 3 * t2 + 1;
    float h1 = -2 * t3 + 3 * t2;

    position->x = h0 * tg->start.x + h1 * tg->end.x;
    position->y = h0 * tg->start.y + h1 * tg->end.y;
    position->z = h0 * tg->start.z + h1 * tg->end.z;

    tg->currentTime += dt;
}

bool trajectoryComplete(TrajectoryGenerator* tg)
{
    return tg->currentTime >= tg->duration;
}

#endif // _CORE_CONTROLLER_TRAJECTORY_C_
