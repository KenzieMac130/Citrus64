/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Memory.h"
#include "engine/tests/UnitTester.h"

#include "codegen/engine/tests/utilities/MemoryTest.c.gen.h"

void ctUnitTestMemory() {
    ctUnitTestAssert(CT_ALIGNMENT_CACHE == 16);

    CT_ALIGN(CT_ALIGNMENT_CACHE) int testVar;
    ctUnitTestAssert((size_t)&testVar % CT_ALIGNMENT_CACHE == 0);

    uint8_t* data = ctAlignedMalloc(64, CT_ALIGNMENT_CACHE);
    ctUnitTestAssert((size_t)data % CT_ALIGNMENT_CACHE == 0);
    memset(data, 3, 64);
    for(size_t i = 0; i < 64; i++){
        ctUnitTestAssert(data[i] == 3);
    }

    data = ctAlignedRealloc(data, 128, CT_ALIGNMENT_CACHE);
    ctUnitTestAssert((size_t)data % CT_ALIGNMENT_CACHE == 0);
    for(size_t i = 0; i < 64; i++){
        ctUnitTestAssert(data[i] == 3);
    }
    memset(data, 5, 128);
    for(size_t i = 0; i < 64; i++){
        ctUnitTestAssert(data[i] == 5);
    }
    ctFree(data);

    uint8_t* sp = ctStackAlloc(32);
    memset(sp, 3, 32);
    for(size_t i = 0; i < 32; i++){
        ctUnitTestAssert(sp[i] == 3);
    }

    uint8_t* g1;
    uint8_t* g2;
    uint8_t* g3;
    struct ctGroupAllocDesc groups[] = {
        {
            .alignment = CT_ALIGNMENT_CACHE,
            .size = 32,
            .output = (void*)&g1
        },
        {
            .alignment = CT_ALIGNMENT_CACHE,
            .size = 32,
            .output = (void*)&g2
        },
        {
            .alignment = CT_ALIGNMENT_CACHE,
            .size = 32,
            .output = (void*)&g3
        }
    };
    size_t gsize;
    void* gptr = ctGroupAlloc(3, groups, &gsize);
    ctUnitTestAssert((size_t)g1 % CT_ALIGNMENT_CACHE == 0);
    ctUnitTestAssert((size_t)g2 % CT_ALIGNMENT_CACHE == 0);
    ctUnitTestAssert((size_t)g3 % CT_ALIGNMENT_CACHE == 0);

    memset(g3, 3, 32);
    memset(g2, 2, 32);
    memset(g1, 1, 32);

    for(size_t i = 0; i < 32; i++){
        ctUnitTestAssert(g1[i] == 1);
    }
    for(size_t i = 0; i < 32; i++){
        ctUnitTestAssert(g2[i] == 2);
    }
    for(size_t i = 0; i < 32; i++){
        ctUnitTestAssert(g3[i] == 3);
    }

    ctBufferAssert(gptr, gsize, g1, 32);
    ctBufferAssert(gptr, gsize, g2, 32);
    ctBufferAssert(gptr, gsize, g3, 32);

    ctFree(gptr);
}