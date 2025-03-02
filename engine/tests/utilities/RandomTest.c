/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Random.h"
#include "engine/tests/UnitTester.h"

#include "codegen/engine/tests/utilities/RandomTest.c.gen.h"

void ctUnitTestRandom() {
   ctRandomGenerator rnd = ctRandomGeneratorInit();
   /*ctDebugLog("Random Numbers %u %f %f",
       ctRandomGetUInt32(&rnd),
       ctRandomGetFloat(&rnd, 0.0f, 5.0f),
       ctVec3Length(ctRandomGetInSphere(&rnd, 0.5f))
   );*/

   for (size_t i = 0; i < 1024; i++) {
      ctUnitTestAssert(ctFloatApproxEqual(ctVec3Length(ctRandomGetVec3Norm(&rnd)), 1.0f));
   }

   for (size_t i = 0; i < 1024; i++) {
      ctUnitTestAssert(ctVec3Length(ctRandomGetInSphere(&rnd, 1.0f)) <= 2.1f);
   }
}