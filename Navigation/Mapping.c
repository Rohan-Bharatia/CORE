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

#ifndef _CORE_NAVIGATION_MAPPING_C_
    #define _CORE_NAVIGATION_MAPPING_C_

#include "Mapping.h"

#include <stdlib.h>
#include <stdio.h>

OccupancyGrid* createGrid(uint32 width, uint32 height, float32 resolution)
{
    OccupancyGrid* grid = (OccupancyGrid*)malloc(sizeof(OccupancyGrid));
    grid->width         = width;
    grid->height        = height;
    grid->resolution    = resolution;
    grid->grid          = (uint8*)malloc(width * height * sizeof(uint8));

    // Initialize as unknown
    for(uint32 i = 0; i < width * height; ++i)
        grid->grid[i] = 128;

    return grid;
}

void updateGrid(OccupancyGrid* grid, Vector2D position, uint8 occupancy)
{
    uint32 gridX = (uint32)(position.x / grid->resolution);
    uint32 gridY = (uint32)(position.y / grid->resolution);

    if(gridX >= grid->width || gridY >= grid->height)
        return;

    uint32 index      = gridY * grid->width + gridX;
    grid->grid[index] = occupancy;
}

uint8 getOccupancy(OccupancyGrid* grid, Vector2D position)
{
    uint32 gridX = (uint32)(position.x / grid->resolution);
    uint32 gridY = (uint32)(position.y / grid->resolution);

    if(gridX >= grid->width || gridY >= grid->height)
        return 0;

    return grid->grid[gridY * grid->width + gridX];
}

void saveGrid(OccupancyGrid* grid, char* filename)
{
    FILE* file = fopen(filename, "wb");
    if(!file)
        return;

    fwrite(&grid->width, sizeof(uint32), 1, file);
    fwrite(&grid->height, sizeof(uint32), 1, file);
    fwrite(&grid->resolution, sizeof(float32), 1, file);
    fwrite(grid->grid, sizeof(uint8), grid->width * grid->height, file);

    fclose(file);
}

#endif // _CORE_NAVIGATION_MAPPING_C_
