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

#ifndef _CORE_VISION_FEATURE_TRACKING_C_
    #define _CORE_VISION_FEATURE_TRACKING_C_

#include "FeatureTracking.h"

#include <math.h>
#include <stdlib.h>

FeatureSet* detectFeatures(Image* img)
{
    FeatureSet* features = (FeatureSet*)malloc(sizeof(FeatureSet));
    features->features   = (Feature*)malloc(sizeof(Feature) * MAX_FEATURES);
    features->count      = 0;

    // Harris corner detection
    float32* responses = (float32*)calloc(img->width * img->height, sizeof(float32));

    for (uint32 y = 1; y < img->height - 1; ++y)
    {
        for (uint32 x = 1; x < img->width - 1; ++x)
        {
            float32 ix  = 0,
                    iy  = 0,
                    ixx = 0,
                    iyy = 0,
                    ixy = 0;

            // Compute gradients
            for (int32 dy = -1; dy <= 1; ++dy)
            {
                for (int32 dx = -1; dx <= 1; ++dx)
                {
                    uint32 idx = (y + dy) * img->width + (x + dx);
                    ix        += dx * img->data[idx];
                    iy        += dy * img->data[idx];
                }
            }

            // Compute second moments
            ixx = ix * ix;
            iyy = iy * iy;
            ixy = ix * iy;

            // Harris response
            float32 det   = ixx * iyy - ixy * ixy;
            float32 trace = ixx + iyy;
            responses[y * img->width + x] = det - 0.04f * trace * trace;
        }
    }

    // Non-maximum suppression
    float32 threshold = 1000.0f;
    for (uint32 y = 2; y < img->height - 2; ++y)
    {
        for (uint32 x = 2; x < img->width - 2; ++x)
        {
            float32 response = responses[y * img->width + x];
            if (response > threshold)
            {
                bool isMax = true;
                for (int32 dy = -2; dy <= 2 && isMax; ++dy)
                {
                    for (int32 dx = -2; dx <= 2; ++dx)
                    {
                        if (dx == 0 && dy == 0)
                            continue;

                        if (responses[(y+dy)*img->width + (x+dx)] >= response)
                        {
                            isMax = false;
                            break;
                        }
                    }
                }

                if (isMax && features->count < MAX_FEATURES)
                {
                    Feature* f    = &features->features[features->count++];
                    f->position.x = x;
                    f->position.y = y;
                    f->response   = response;

                    // Compute orientation
                    float32 dx     = img->data[y * img->width + x + 1] - img->data[y * img->width + x - 1];
                    float32 dy     = img->data[(y + 1) * img->width + x] - img->data[(y - 1) * img->width + x];
                    f->orientation = atan2f(dy, dx);
                }
            }
        }
    }

    free(responses);
    return features;
}

void trackFeatures(Image* prev, Image* curr, FeatureSet* features)
{
    // Lucas-Kanade optical flow
    const int32 windowSize = 7;
    const int32 maxIter    = 10;
    const float32 minDelta = 0.01f;

    for (uint32 i = 0; i < features->count; ++i)
    {
        Vector2D* pos = &features->features[i].position;
        int32 x       = (int32)pos->x;
        int32 y       = (int32)pos->y;

        float32 dx = 0,
                dy = 0;
        for (int32 iter = 0; iter < maxIter; ++iter)
        {
            float32 a[4] = { 0 },
                    b[2] = { 0 };

            for (int32 wy = -windowSize / 2; wy <= windowSize / 2; ++wy)
            {
                for (int32 wx = -windowSize / 2; wx <= windowSize / 2; ++wx)
                {
                    int32 px = x + wx;
                    int32 py = y + wy;

                    if (px < 1 || px >= prev->width - 1 || py < 1 || py >= prev->height - 1)
                        continue;

                    float32 ix = (prev->data[py * prev->width + px + 1] -
                                  prev->data[py * prev->width + px - 1]) / 2.0f;
                    float32 iy = (prev->data[(py + 1) * prev->width + px] -
                                  prev->data[(py - 1) * prev->width + px]) / 2.0f;
                    float32 it = curr->data[py * curr->width + px] -
                                 prev->data[py * prev->width + px];

                    a[0] += ix * ix;
                    a[1] += ix * iy;
                    a[2] += ix * iy;
                    a[3] += iy * iy;
                    b[0] += -ix * it;
                    b[1] += -iy * it;
                }
            }

            // Solve 2x2 system
            float32 det = a[0] * a[3] - a[1] * a[2];
            if (fabsf(det) < 1e-6f)
                break;

            float32 vx = (a[3] * b[0] - a[1] * b[1]) / det;
            float32 vy = (-a[2] * b[0] + a[0] * b[1]) / det;

            dx += vx;
            dy += vy;

            if (vx*vx + vy*vy < minDelta*minDelta)
                break;
        }

        pos->x += dx;
        pos->y += dy;
    }
}

void releaseFeatureSet(FeatureSet* features)
{
    if (features)
    {
        free(features->features);
        free(features);
    }
}

#endif // _CORE_VISION_FEATURE_TRACKING_C_
