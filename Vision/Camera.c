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

#ifndef _CORE_VISION_CAMERA_C_
    #define _CORE_VISION_CAMERA_C_

#include "Camera.h"

#include "../Controller/Geometry.h"

#include <math.h>
#include <stdlib.h>

Image* capturePinhole(void* camera)
{
    Camera* cam  = (Camera*)camera;
    Image* image = createImage(cam->focalWidth, cam->sensorHeight);
    for (uint32 y = 0; y < image->height; ++y)
    {
        for (uint32 x = 0; x < image->width; ++x)
            // Get the pixel value
            image->data[y * image->width + x] = ((x + y) % 256);
    }
    return image;
}

Image* captureFisheye(void* camera)
{
    Camera* cam  = (Camera*)camera;
    Image* image = createImage(cam->focalWidth, cam->sensorHeight);

    for (uint32 y = 0; y < image->height; ++y)
    {
        for (uint32 x = 0; x < image->width; ++x)
        {
            float32 r          = sqrt((x - image->width / 2) * (x - image->width / 2) + (y - image->height / 2) * (y - image->height / 2));
            float32 theta      = atan2(y - image->height / 2, x - image->width / 2);
            float32 distortedR = r * (1 + cam->distortionCoefficents[0] * r * r + cam->distortionCoefficents[1] * r * r * r * r);
            uint32 distortedX  = (uint32)(distortedR * cos(theta) + image->width / 2);
            uint32 distortedY  = (uint32)(distortedR * sin(theta) + image->height / 2);
            if (distortedX >= 0 && distortedX < image->width && distortedY >= 0 && distortedY < image->height)
                image->data[y * image->width + x] = (uint8)((distortedX + distortedY) % 256);
            else
                image->data[y * image->width + x] = 0;
        }
    }

    return image;
}

Image* captureOmnidirectional(void* camera)
{
    Camera* cam = (Camera*)camera;
    Image* image = createImage(cam->focalWidth, cam->sensorHeight);
    // Simulate omnidirectional camera capture (e.g., using a mirror or lens)
    // For simplicity, just fill the image with a panoramic view
    for (uint32 y = 0; y < image->height; y++) {
        for (uint32 x = 0; x < image->width; x++) {
            float32 theta      = (x - image->width / 2) * 2 * PI / image->width;
            float32 phi        = (y - image->height / 2) * PI / image->height;
            float32 r          = sqrt(cam->focalLength * cam->focalLength + cam->focalWidth * cam->focalWidth / 4);
            float32 distortedX = (uint32)(r * sin(phi) * cos(theta) + image->width / 2);
            float32 distortedY = (uint32)(r * sin(phi) * sin(theta) + image->height / 2);
            if (distortedX >= 0 && distortedX < image->width && distortedY >= 0 && distortedY < image->height)
                image->data[y * image->width + x] = ((uint8)(distortedX + distortedY) % 256);
            else
                image->data[y * image->width + x] = 0;
        }
    }
    return image;
}

Camera* cameraInitialize(uint8 model, float32 focalLength, float32 focalWidth, float32 sensorHeight)
{
    Camera* camera = malloc(sizeof(Camera));

    camera->model                    = model;
    camera->focalLength              = focalLength;
    camera->focalWidth               = focalWidth;
    camera->sensorHeight             = sensorHeight;
    camera->distortionCoefficents[0] = 0.0f;
    camera->distortionCoefficents[1] = 0.0f;
    camera->distortionCoefficents[2] = 0.0f;
    camera->distortionCoefficents[3] = 0.0f;
    camera->distortionCoefficents[4] = 0.0f;

    switch (model)
    {
        case CAMERA_MODEL_PINHOLE:
            camera->capture = capturePinhole;
            return camera;
        case CAMERA_MODEL_FISHEYE:
            camera->capture = captureFisheye;
            return camera;
        case CAMERA_MODEL_OMNIDIRECTIONAL:
            camera->capture = captureOmnidirectional;
            return camera;
        default:
            camera->capture = NULL;
            return camera;
    }
}

#endif // _CORE_VISION_CAMERA_C_
