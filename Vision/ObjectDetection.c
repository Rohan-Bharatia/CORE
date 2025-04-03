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

#ifndef _CORE_VISION_OBJECT_DETECTION_C_
    #define _CORE_VISION_OBJECT_DETECTION_C_

#include "ObjectDetection.h"

#include <math.h>
#include <stdlib.h>

DetectionResult* detectObjects(Image* img)
{
    DetectionResult* result = (DetectionResult*)malloc(sizeof(DetectionResult));
    result->boxes           = (BoundingBox*)malloc(sizeof(BoundingBox) * 10); // Max 10 objects
    result->count           = 0;

    // Simple blob detection
    uint32 minBlobSize = 100;
    uint8* visited     = (uint8*)calloc(img->width * img->height, sizeof(uint8));

    for (uint32 y = 1; y < img->height - 1; ++y)
    {
        for (uint32 x = 1; x < img->width - 1; ++x)
        {
            if (img->data[y*img->width + x] > 128 && !visited[y*img->width + x])
            {
                // Found potential object, flood fill to find bounds
                uint32 minX = x,
                       maxX = x,
                       minY = y,
                       maxY = y,
                       size = 0;

                // Simple flood fill
                uint32 stack[1000];
                uint32 stackPtr   = 0;
                stack[stackPtr++] = y * img->width + x;

                while (stackPtr > 0)
                {
                    uint32 pos = stack[--stackPtr];
                    uint32 cy  = pos / img->width;
                    uint32 cx  = pos % img->width;

                    if (visited[pos] || img->data[pos] <= 128)
                        continue;

                    visited[pos] = 1;
                    size++;

                    minX = (cx < minX) ? cx : minX;
                    maxX = (cx > maxX) ? cx : maxX;
                    minY = (cy < minY) ? cy : minY;
                    maxY = (cy > maxY) ? cy : maxY;

                    // Add neighbors to stack
                    if (cx > 0)
                        stack[stackPtr++] = pos - 1;
                    if (cx < img->width - 1)
                        stack[stackPtr++] = pos + 1;
                    if (cy > 0)
                        stack[stackPtr++] = pos - img->width;
                    if (cy < img->height - 1)
                        stack[stackPtr++] = pos + img->width;
                }

                if (size > minBlobSize && result->count < 10)
                {
                    BoundingBox* box = &result->boxes[result->count++];
                    box->position.x  = (minX + maxX) / 2.0f;
                    box->position.y  = (minY + maxY) / 2.0f;
                    box->width       = maxX - minX;
                    box->height      = maxY - minY;
                    box->confidence  = size / (float32)(img->width * img->height);
                }
            }
        }
    }

    free(visited);
    return result;
}

void releaseObjectDetectionResult(DetectionResult* result)
{
    if (result)
    {
        free(result->boxes);
        free(result);
    }
}

float32 computeIOU(BoundingBox* b1, BoundingBox* b2)
{
    float32 x1 = fmaxf(b1->position.x - b1->width / 2, b2->position.x - b2->width / 2);
    float32 y1 = fmaxf(b1->position.y - b1->height / 2, b2->position.y - b2->height / 2);
    float32 x2 = fminf(b1->position.x + b1->width / 2, b2->position.x + b2->width / 2);
    float32 y2 = fminf(b1->position.y + b1->height / 2, b2->position.y + b2->height / 2);

    float32 intersection = fmaxf(0, x2 - x1) * fmaxf(0, y2 - y1);
    float32 unionArea    = b1->width * b1->height + b2->width * b2->height - intersection;

    return intersection / unionArea;
}

#endif // _CORE_VISION_OBJECT_DETECTION_C_
