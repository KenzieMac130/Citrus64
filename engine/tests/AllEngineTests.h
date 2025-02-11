/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "codegen/engine/tests/AllEngineTests.h.gen.h"

extern void ctUnitTestMemory();
extern void ctUnitTestString();
extern void ctUnitTestMath();
extern void ctUnitTestMath3D();
extern void ctUnitTestHash();
extern void ctUnitTestHashTable();
extern void ctUnitTestRandom();

/* see ctUnitTest (name, function, requires engine) */
// clang-format off
#define CT_ALL_TESTS \
    {"Memory", ctUnitTestMemory, false},\
    {"String", ctUnitTestString, false},\
    {"Math", ctUnitTestMath, false},\
    {"Math3D", ctUnitTestMath3D, false},\
    {"Hash", ctUnitTestHash, false},\
    {"HashTable", ctUnitTestHashTable, false},\
    {"Random", ctUnitTestRandom, false}
// clang-format on