/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/resource/Resource.h"

#include "codegen/engine/tests/resource/ResourceTest.c.gen.h"

CT_XXH32_STRING(RTEST_TRANS, "__TEST__")

void ctUnitTestResource() {
   ctResourceManagerStartup();
   ctResourceHandle sprite;
   ctResourceHandle model;
   ctResourceHandle font;
   ctResourceHandle translation;
   // clang-format off
   ctUnitTestAssert(ctResourceGetOrLoad(&sprite,
                                        CT_RESOURCE_SPRITE,
                                        "core/sprite/NULLSPRITE") == CT_SUCCESS);
   ctUnitTestAssert(ctResourceGetOrLoad(&model,
                                        CT_RESOURCE_MODEL,
                                        "core/model/NULLMODEL") == CT_SUCCESS);
   ctUnitTestAssert(ctResourceGetOrLoad(&font,
                                        CT_RESOURCE_FONT,
                                        "core/font/NotoSansJP-Medium") == CT_SUCCESS);
   ctUnitTestAssert(ctResourceGetOrLoad(&translation,
                                        CT_RESOURCE_TRANSLATION,
                                        "core/text/core-en") == CT_SUCCESS);
   // clang-format on
   //const char* result = ctResourceGetTextHashed(translation, RTEST_TRANS);
   //ctDebugLog("Translation: %s", result);

   ctResourceRelease(sprite);
   ctResourceRelease(model);
   ctResourceRelease(font);
   ctResourceRelease(translation);

   ctResourceManagerShutdown();
}