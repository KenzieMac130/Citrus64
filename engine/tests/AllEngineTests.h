/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

extern void ctUnitTestMemory();
extern void ctUnitTestString();
extern void ctUnitTestMath();

/* see ctUnitTest (name, function, requires engine) */
#define CT_ALL_TESTS \
    {"Memory", ctUnitTestMemory, false},\
    {"String", ctUnitTestString, false},\
    {"Math", ctUnitTestMath, false}

