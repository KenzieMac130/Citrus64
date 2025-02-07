/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "Common.h"

/* ------- Alignment ------- */

#define CT_ALIGNMENT_CACHE 16
#define CT_ALIGN(x) alignas(x)

/* ------- Dynamic Memory Allocation -------*/

void* ctMalloc(size_t size);
void* ctRealloc(void* old, size_t size);
void ctFree(void* block);
void* ctAlignedMalloc(size_t size, size_t alignment);
void* ctAlignedRealloc(void* block, size_t size, size_t alignment);
void ctAlignedFree(void* block);

struct ctGroupAllocDesc {
   size_t alignment;
   size_t size;
   void** output;
};
void* ctGroupAlloc(size_t count, struct ctGroupAllocDesc* groups, size_t* pSizeOut);

#define ctStackAlloc(_SIZE) alloca(_SIZE)

/* this does not include allocations made by vanilla malloc/free */
int64_t ctGetAliveAllocations();

/* ------- Buffer Over/Underflow Checking ------- */

void ctBufferAssert(void* parentBuffer, size_t parentBufferSize, void* childBuffer, size_t childBufferSize);

/* Single pointers */

#define ctBufferAssertSingle(_parentBuffer, _parentBufferSize, _ptr) \
ctBufferAssert(_parentBuffer, _parentBufferSize, _ptr, sizeof(_ptr))

/* Ranges (ptr, ptr) */

#define ctBufferAssertRange(_parentBuffer, _parentBufferSize, _ptrMin, _ptrMax) \
ctBufferAssert(_parentBuffer, _parentBufferSize, _ptrMin, (size_t)(_ptrMax - _ptrMin))

/* Indices */

#define ctBufferAssertIndex(_parentBuffer, _parentBufferSize, _idx) \
ctBufferAssertSingle(_parentBuffer, _parentBufferSize, _parentBuffer + _idx)
