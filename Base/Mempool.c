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

#ifndef _CORE_BASE_MEMPOOL_C_
    #define _CORE_BASE_MEMPOOL_C_

#include "Mempool.h"

#include <stdlib.h>

MemPool* createPool(opsize blockSize, uint32 blockCount)
{
    MemPool* pool = (MemPool*)malloc(sizeof(MemPool));

    pool->start      = malloc(blockCount * blockSize);
    pool->blockSize  = blockSize;
    pool->blockCount = blockCount;
    pool->freeBlocks = blockCount;
    pool->bitmap     = (uint8*)calloc((blockCount + 7) / 8, 1);

    return pool;
}

void* poolAlloc(MemPool* pool)
{
    if (!pool || pool->freeBlocks == 0)
        return NULL;

        for (uint32 i = 0; i < pool->blockCount; ++i)
        {
            if (!(pool->bitmap[i / 8] & (1 << (i % 8))))
            {
                pool->bitmap[i / 8] |= (1 << (i % 8));
                --pool->freeBlocks;
                return (void*)((char*)pool->start + (i * pool->blockSize));
            }
        }
        return NULL;
}

void poolFree(MemPool* pool, void* ptr)
{
    if (!pool || !ptr)
        return;

        opsize offset = ((char*)ptr - (char*)pool->start);
        uint32 index  = offset / pool->blockSize;

        if (index < pool->blockCount)
        {
            pool->bitmap[index / 8] &= ~(1 << (index % 8));
            ++pool->freeBlocks;
        }
}

void destroyPool(MemPool* pool)
{
    if (pool)
    {
        free(pool->start);
        free(pool->bitmap);
        free(pool);
    }
}

#endif // _CORE_BASE_MEMPOOL_C_
