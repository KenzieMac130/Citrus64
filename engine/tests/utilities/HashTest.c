/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/Common.h"

#include "codegen/engine/tests/utilities/HashTest.c.gen.h"

void ctUnitTestHash() {
    ctUnitTestAssert(ctXXHash32String("Hello World!") == CT_XXH32_STRING(Hello_World, "Hello World!"));
}