/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/Common.h"

#include "codegen/engine/tests/utilities/HashTest.c.gen.h"

CT_XXH32_STRING(TEST_HASH, "Hello World!")

void ctUnitTestHash() {
    ctUnitTestAssert(ctXXHash32String("Hello World!") == TEST_HASH);
}