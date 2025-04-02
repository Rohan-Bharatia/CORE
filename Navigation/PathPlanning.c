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

#ifndef _CORE_NAVIGATION_PATH_PLANNING_C_
    #define _CORE_NAVIGATION_PATH_PLANNING_C_

#include "PathPlanning.h"

#include <math.h>
#include <stdlib.h>

float32 distanceToLineSegment(Vector3D* start, Vector3D* end, Vector3D* point)
{
    float32 l2 = (end->x - start->x) * (end->x - start->x) + (end->y - start->y) * (end->y - start->y) + (end->z - start->z) * (end->z - start->z);
    float32 t  = ((point->x - start->x) * (end->x - start->x) + (point->y - start->y) * (end->y - start->y) + (point->z - start->z) * (end->z - start->z)) / l2;
    if(t < 0.0f)
        t = 0.0f;
    if(t > 1.0f)
        t = 1.0f;
    float32 x = start->x + t * (end->x - start->x);
    float32 y = start->y + t * (end->y - start->y);
    float32 z = start->z + t * (end->z - start->z);
    return sqrtf((point->x - x) * (point->x - x) + (point->y - y) * (point->y - y) + (point->z - z) * (point->z - z));
}

float32 distance(Vector3D* a, Vector3D* b)
{
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
}

Path* pathPlan(Vector3D* start, Vector3D* goal, Vector3D* obstacles, uint32 obstacleCount)
{
    Path* path          = (Path*)malloc(sizeof(Path));
    path->waypoints     = (Vector3D*)malloc(sizeof(Vector3D) * MAX_PATH_LENGTH);
    path->waypointCount = 2;
    path->pathLength    = 0.0f;

    // Simple direct path initially
    path->waypoints[0] = *start;
    path->waypoints[1] = *goal;

    // Check for collisions and add waypoints to avoid obstacles
    for(uint32 i = 0; i < obstacleCount; ++i)
    {
        if(!pathIsClear(path, &obstacles[i], 1))
        {
            Vector3D midpoint =
            {
                (start->x + goal->x) * 0.5f + obstacles[i].y - obstacles[i].y,
                (start->y + goal->y) * 0.5f - obstacles[i].x + obstacles[i].x,
                (start->z + goal->z) * 0.5f
            };
            path->waypoints[path->waypointCount++] = midpoint;
        }
    }

    pathOptimize(path);
    return path;
}

bool pathIsClear(Path* path, Vector3D* obstacles, uint32 obstacleCount)
{
    for(uint32 i = 0; i < path->waypointCount - 1; ++i)
    {
        Vector3D* start = &path->waypoints[i];
        Vector3D* end   = &path->waypoints[i + 1];

        for(uint32 j = 0; j < obstacleCount; ++j)
        {
            float32 dist = distanceToLineSegment(start, end, &obstacles[j]);
            if(dist < COLLISION_THRESHOLD)
                return false;
        }
    }
    return true;
}

void pathOptimize(Path* path)
{
    path->pathLength = 0.0f;
    for(uint32 i = 0; i < path->waypointCount - 1; ++i)
        path->pathLength += distance(&path->waypoints[i], &path->waypoints[i + 1]);
}

#endif // _CORE_NAVIGATION_PATH_PLANNING_C_
