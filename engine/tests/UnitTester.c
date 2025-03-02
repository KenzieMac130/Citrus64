/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "UnitTester.h"
#include "AllEngineTests.h"

#include "engine/core/EngineCore.h"

#include "codegen/engine/tests/UnitTester.c.gen.h"

const struct ctUnitTest gAllEngineTests[] = {CT_ALL_TESTS, {NULL, NULL, false}};

void ctUnitTestRun(const struct ctUnitTest* unitTest) {
   if (unitTest->requireEngine) { /* initialize engine */
      ctEngineIgnite();
   }
   ctDebugLog("Running Test (%s)...", unitTest->name);
   unitTest->function();
   if (unitTest->requireEngine) { /* shutdown engine */
      ctEngineShutdown();
   }
}

void ctUnitTestRunArray(const struct ctUnitTest* unitTests) {
   for (; unitTests->function != NULL; unitTests++) {
      ctUnitTestRun(unitTests);
   }
}

int _ctUnitTestsMain() {
   console_init();
   console_set_debug(true);
   console_set_render_mode(RENDER_AUTOMATIC);
   ctUnitTestRunArray(gAllEngineTests);
   ctDebugLog("Finished!");
   while (1) {}
   return 0;
}