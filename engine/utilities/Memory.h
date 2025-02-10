/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Memory.h

Memory allocation and manipulation utilities
*/
#pragma once

#include "Common.h"

#include "codegen/engine/utilities/Memory.h.gen.h"

/* ------- Alignment ------- */

/*! @brief The size of the platform's CPU cache line */
#define CT_ALIGNMENT_CACHE 16

/*! @brief alignas macro wrapper */
#define CT_ALIGN(x) alignas(x)

/* ------- Dynamic Memory Allocation -------*/

/*! @brief Heap memory allocation

   Similar to C's malloc() but guaranteed to sit on CT_ALIGNMENT_CACHE
   @warning Only free with ctFree()
*/
void* ctMalloc(size_t size);

/*! @brief Heap memory reallocation

   Similar to C's realloc() but guaranteed to sit on CT_ALIGNMENT_CACHE
   @warning Only free with ctFree()
*/
void* ctRealloc(void* old, size_t size);

/*! @brief Heap memory free

   Similar to C's free() but for use with ctAlloc functions
   @warning Only use on blocks allocated with ctAlloc variants
*/
void ctFree(void* block);

/*! @brief Aligned heap memory allocation

   Similar to C's malloc() but guaranteed to be aligned
   @warning Only free with ctFree()
*/
void* ctAlignedMalloc(size_t size, size_t alignment);

/*! @brief Aligned heap memory reallocation

   Similar to C's malloc() but guaranteed to be aligned
   @warning Only free with ctFree()
*/
void* ctAlignedRealloc(void* block, size_t size, size_t alignment);

/*! @brief Aligned heap memory free

   Basically just ctFree(). Its here for API symetry.
*/
void ctAlignedFree(void* block);

/*! @brief Allocation group descriptor for ctGroupAlloc() */
typedef struct {
   /*! alignment of block */
   size_t alignment;
   /*! size of block */
   size_t size;
   /*! pointer to write the sub-allocation address to */
   void** output;
} ctGroupAllocDesc;

/*! @brief Optimized group allocation

   Instead of allocating blocks of data which will share similar lifetime seperately you
   can use this function to allocate a single block of data which can be shared by
   multiple members of a data structure.

   @param count number of groups to pass
   @param groups list of groups and their allocation descriptions
   @param sizeOut (optional) returns the size of the resulting allocation
   @returns A pointer to the shared block of data
   @warning Only call ctFree() on the shared block
*/
void* ctGroupAlloc(size_t count, ctGroupAllocDesc* groups, size_t* sizeOut);

/*! @brief Allocate memory on the stack
   @warning Only use for small allocations whose size cannot be known at compile time
*/
#define ctStackAlloc(_SIZE) alloca(_SIZE)

/*! @brief Get the number of allocations that exist right now

   This does not include allocations made by vanilla malloc/free
*/
int64_t ctGetAliveAllocations();

/* ------- Buffer Over/Underflow Checking ------- */

/*! @brief Assert memory block against parent bounds */
void ctBufferAssert(void* parentBuffer,
                    size_t parentBufferSize,
                    void* childBuffer,
                    size_t childBufferSize);

/*! @brief ctBufferAssert() for single objects */
#define ctBufferAssertSingle(_parentBuffer, _parentBufferSize, _ptr)                     \
   ctBufferAssert(_parentBuffer, _parentBufferSize, _ptr, sizeof(_ptr))

/*! @brief ctBufferAssert() for a begin-end pointer pair */
#define ctBufferAssertRange(_parentBuffer, _parentBufferSize, _ptrMin, _ptrMax)          \
   ctBufferAssert(_parentBuffer, _parentBufferSize, _ptrMin, (size_t)(_ptrMax - _ptrMin))

/*! @brief ctBufferAssert() for a array indexing */
#define ctBufferAssertIndex(_parentBuffer, _parentBufferSize, _idx)                      \
   ctBufferAssertSingle(_parentBuffer, _parentBufferSize, _parentBuffer + _idx)
