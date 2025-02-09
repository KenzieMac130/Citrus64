/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/String.h"

#include "codegen/engine/tests/utilities/StringTest.c.gen.h"

void ctUnitTestString() {
    /* ------- Comparison ------- */
    ctUnitTestAssert(ctStringCmp("String A", "String B") != 0);
    ctUnitTestAssert(ctStringCmp("String", "String") == 0);
    ctUnitTestAssert(ctStringCmp("String", "string") != 0);

    /* ------- Common ------- */
    ctUnitTestAssert(ctStringByteSize("Hello!") == 7);
    ctUnitTestAssert(ctStringGetUnicodeCodepointCount("こにちは!") == 6);

    char str[4] = {'A', 'B', 'C', 'D'};
    ctStringEnsureNullTerminated(str, 4);
    ctStringEnsureUnicodeValid(str, 4);
    ctUnitTestAssert(ctStringEqual(str, "ABC"));

    /* ------- Case ------- */
    ctStringToLower(str);
    ctUnitTestAssert(ctStringEqual(str, "abc"));
    ctStringToUpper(str);
    ctUnitTestAssert(ctStringEqual(str, "ABC"));
}