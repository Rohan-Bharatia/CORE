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

#ifndef _CORE_VISION_SENSOR_PROCESSING_C_
    #define _CORE_VISION_SENSOR_PROCESSING_C_

#include "ImageProcessing.h"

#include <math.h>
#include <stdlib.h>

Image* createImage(uint32 width, uint32 height)
{
    Image* img = (Image*)malloc(sizeof(Image));

    img->width  = width;
    img->height = height;
    img->data   = (uint8*)malloc(width * height * sizeof(uint8));

    return img;
}

void destroyImage(Image* img)
{
    if (img)
    {
        free(img->data);
        free(img);
    }
}

void imageThreshold(Image* img, uint8 threshold)
{
    for (uint32 i = 0; i < img->width * img->height; ++i)
        img->data[i] = (img->data[i] > threshold) ? 255 : 0;
}

void gaussianBlur(Image* img, uint32 kernelSize)
{
    uint8* temp   = (uint8*)malloc(img->width * img->height);
    float32 sigma = kernelSize / 6.0f;

    // Create Gaussian kernel
    float32* kernel = (float32*)malloc(kernelSize * kernelSize * sizeof(float32));
    float32 sum     = 0.0f;

    for (uint32 i = 0; i < kernelSize; ++i)
    {
        for (uint32 j = 0; j < kernelSize; ++j)
        {
            int32 x                    = i - (kernelSize / 2);
            int32 y                    = j - (kernelSize / 2);
            kernel[i * kernelSize + j] = expf(-(x * x + y * y)/(2 * sigma * sigma));
            sum                       += kernel[i * kernelSize + j];
        }
    }

    // Normalize kernel
    for (uint32 i = 0; i < kernelSize * kernelSize; ++i)
        kernel[i] /= sum;

    // Apply convolution
    for (uint32 y = kernelSize / 2; y < img->height - kernelSize / 2; ++y)
    {
        for (uint32 x = kernelSize / 2; x < img->width - kernelSize / 2; ++x) {
            float32 sum = 0.0f;
            for (uint32 ky = 0; ky < kernelSize; ky++)
            {
                for (uint32 kx = 0; kx < kernelSize; kx++)
                    sum += img->data[(y+ky-kernelSize/2)*img->width + (x+kx-kernelSize/2)] * kernel[ky*kernelSize + kx];
            }
            temp[y*img->width + x] = (uint8)sum;
        }
    }

    free(kernel);
    free(img->data);
    img->data = temp;
}

void sobelEdgeDetection(Image* img)
{
    int8 sobelX[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    int8 sobelY[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
    uint8* temp    = (uint8*)malloc(img->width * img->height);

    for (uint32 y = 1; y < img->height - 1; ++y)
    {
        for (uint32 x = 1; x < img->width - 1; ++x)
        {
            float32 gx = 0.0f;
            float32 gy = 0.0f;

            for (int32 ky = -1; ky <= 1; ++ky)
            {
                for (int32 kx = -1; kx <= 1; ++kx)
                {
                    uint32 idx  = (y + ky) * img->width + (x + kx);
                    uint32 kidx = (ky + 1) * 3 + (kx + 1);
                    gx         += img->data[idx] * sobelX[kidx];
                    gy         += img->data[idx] * sobelY[kidx];
                }
            }

            temp[y * img->width + x] = (uint8)sqrtf(gx * gx + gy * gy);
        }
    }

    free(img->data);
    img->data = temp;
}
void erode(Image* img, uint32 kernelSize)
{}

void dilate(Image* img, uint32 kernelSize)
{}

#endif // _CORE_VISION_SENSOR_PROCESSING_C_
