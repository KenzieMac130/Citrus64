/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/resource/Resource.h"
#include "engine/core/Translation.h"

#include "codegen/engine/tests/core/TranslationTest.c.gen.h"

void ctUnitTestTranslation() {
    ctResourceManagerStartup();
    ctTranslationStartup();

    ctUnitTestAssert(ctStringEqual(ctGetText("__TEST__"), "VALID"));
    ctUnitTestAssert(ctStringEqual(CT_TEXT(__TEST__), "VALID"));
    ctUnitTestAssert(ctStringEqual(CT_TEXT(MY_TEXT), "Exampe text here!!!"));

    ctTranslationShutdown();
    ctResourceManagerShutdown();
}