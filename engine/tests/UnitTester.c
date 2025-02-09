/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "UnitTester.h"
#include "AllEngineTests.h"

#include "codegen/engine/tests/UnitTester.c.gen.h"

void tester() {
    char* bytes = ctMalloc(32);
    ctStringCopy(bytes, 32, "Test");
    ctDebugLog(bytes);
}

const struct ctUnitTest gAllEngineTests[] = {
    CT_ALL_TESTS,
    {NULL, NULL, false}
};

void ctUnitTestRun(const struct ctUnitTest* unitTest) {
    if(unitTest->requireEngine){
        /* initialize engine */
    }
    ctDebugLog("Running Test (%s)...", unitTest->name);
    unitTest->function();
    if(unitTest->requireEngine){
        /* shutdown engine */
    }
    console_render();
}

void ctUnitTestRunArray(const struct ctUnitTest* unitTests){
    for(; unitTests->function != NULL; unitTests++){
        ctUnitTestRun(unitTests);
    }
}

int _ctUnitTestsMain() {
    ctUnitTestRunArray(gAllEngineTests);
    ctDebugLog("Finished!");
    console_render();
    while (1){}
    return 0;
}