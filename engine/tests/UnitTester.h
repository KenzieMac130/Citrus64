/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "engine/utilities/Common.h"

struct ctUnitTest {
    const char* name;
    void(*function)(void);
    bool requireEngine;
};

#if CT_IS_DEBUG
#define ctUnitTestAssert(_expression) ctAssert(_expression)
#else
#define ctUnitTestAssert(_expression) _expression
#endif

int _ctUnitTestsMain();