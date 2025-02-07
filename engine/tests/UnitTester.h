/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "engine/utilities/Common.h"

struct ctUnitTest {
    const char* name;
    void(*function)(void);
    bool requireEngine;
};

int _ctUnitTestsMain();