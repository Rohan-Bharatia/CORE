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

#ifndef _CORE_VISION_CAMERA_H_
    #define _CORE_VISION_CAMERA_H_

#include "ImageProcessing.h"

#define CAMERA_MODEL_PINHOLE         0
#define CAMERA_MODEL_FISHEYE         1
#define CAMERA_MODEL_OMNIDIRECTIONAL 2

typedef struct
{
    uint8 model;
    float32 focalLength;
    float32 focalWidth;
    float32 sensorHeight;
    float32 distortionCoefficents[5];

    Image* (*capture)(void* camera);
} Camera;

Camera* cameraInitialize(uint8 model, float32 focalLength, float32 focalWidth, float32 sensorHeight);

#endif // _CORE_VISION_CAMERA_H_
