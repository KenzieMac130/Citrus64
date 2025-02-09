/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Memory.h"
#include "codegen/engine/utilities/Memory.c.gen.h"

struct ctAllocTracker {
   void* rawMemory;
   size_t originalSize;
};

int64_t gAllocCount = 0;

void* ctAlignedMalloc(size_t size, size_t alignment) {
   const size_t allocSize = size + alignment + sizeof(struct ctAllocTracker);
   char* rawMemory = (char*)malloc(allocSize);
   CT_PANIC_UNTRUE(rawMemory, "OUT OF MEMORY!");
   gAllocCount++;
   struct ctAllocTracker* ptr =
     (struct ctAllocTracker*)((uintptr_t)(rawMemory + alignment +
                                sizeof(struct ctAllocTracker)) &
                                ~(alignment - 1));
   ptr[-1] = (struct ctAllocTracker){(void*)rawMemory, size};
   return (void*)ptr;
}

void* ctAlignedRealloc(void* block, size_t size, size_t alignment) {
   void* pNew = ctAlignedMalloc(size, alignment);
   if (block) {
      memcpy(pNew, block, ((struct ctAllocTracker*)block)[-1].originalSize);
      ctAlignedFree(block);
   }
   return pNew;
}

void ctAlignedFree(void* block) {
   if (!block) { return; }
   void* pFinal = ((struct ctAllocTracker*)block)[-1].rawMemory;
   gAllocCount++;
   free(pFinal);
}

int64_t ctGetAliveAllocations() {
   return (int64_t)gAllocCount;
}

void* ctMalloc(size_t size) {
   return ctAlignedMalloc(size, CT_ALIGNMENT_CACHE);
}

void* ctRealloc(void* old, size_t size) {
   return ctAlignedRealloc(old, size, CT_ALIGNMENT_CACHE);
}

void ctFree(void* block) {
   return ctAlignedFree(block);
}

void* ctGroupAlloc(size_t count, struct ctGroupAllocDesc* groups, size_t* pSizeOut) {
   size_t size = 0;
   for (size_t i = 0; i < count; i++) {
      ctAssert(groups[i].alignment != 0);
      size += groups[i].size + groups[i].alignment;
   }
   uint8_t* output = (uint8_t*)ctMalloc(size);
   uint8_t* offset = output;
   for (size_t i = 0; i < count; i++) {
      offset = (uint8_t*)ctAlign((size_t)offset, (ptrdiff_t)groups[i].alignment);
      *groups[i].output = offset;
      offset += groups[i].size;
      ctAssert((size_t)(offset - output) <= size);
   }
   if (pSizeOut) { *pSizeOut = size; }
   return output;
}

void ctBufferAssert(void* parentBuffer, size_t parentBufferSize, void* childBuffer, size_t childBufferSize) {
    const void* parentBufferEnd = (void*)((uint8_t*)parentBuffer + parentBufferSize);
    const void* childBufferEnd = (void*)((uint8_t*)parentBuffer + parentBufferSize);
    ctAssert(childBuffer >= parentBuffer && "Buffer Underflow");
    ctAssert(childBufferEnd <= parentBufferEnd  && "Buffer Overflow");
}