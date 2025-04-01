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

#ifndef _CORE_CONTROLLER_GEOMETRY_H_
    #define _CORE_CONTROLLER_GEOMETRY_H_

#include "../Base/Types.h"

// Common math constants
#define PI 3.14159265358979323846
#define E  2.71828182845904523536

// 2D Vector structure
typedef struct
{
    float32 x;
    float32 y;
} Vector2D;

// 3D Vector structure
typedef struct
{
    float32 x;
    float32 y;
    float32 z;
} Vector3D;

// Quaternion structure for rotations
typedef struct
{
    float32 w;
    float32 x;
    float32 y;
    float32 z;
} Vector4D, Quaternion;

// Matrix structure for transformations
typedef struct
{
    float32 data[4][4];
} Matrix4x4;

#endif // _CORE_CONTROLLER_GEOMETRY_H_
