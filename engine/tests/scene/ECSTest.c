/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/Utilities.h"

#include "engine/scene/BuiltinComponents.h"

#include "codegen/engine/tests/scene/ECSTest.c.gen.h"

#if CT_BUILD_UNIT_TESTS
CT_DEFINE_COMPONENT(UTest, ctVec3, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);
CT_DEFINE_ECS_FLAGS(Renderable);
CT_DEFINE_ECS_FLAGS(A);
CT_DEFINE_ECS_FLAGS(B);
CT_DEFINE_ECS_FLAGS(C);

void ctUnitTestECS() {
   ctECSInitializeUTest();

   ctECSAddGroundPlane(0);

   ctECSSetFlagRenderable(0);
   ctECSUnsetFlagRenderable(0);
   ctECSGetFlagRenderable(0);

   for (uint32_t i = 1; i < 90; i++) {
      ctVec3* pos = ctECSAddUTest(i);
      ctAssert(pos);
      pos->x = (float)i;
      pos->y = 32.0f;
      pos->z = -32.0f;
      ctECSSetFlagA(i);
      ctECSSetFlagB(i);
      ctECSSetFlagC(i);
   }

   for (uint32_t i = 0; i < ctECSItCountA(); i++) {
      if (ctECSItGetStateA(i)) {
         ctEntity e = ctECSItGetEntityA(i);
         ctECSGetUTest(e)->z += 32;
      }
   }

   ctECSRemoveUTest(2);
   ctECSRemoveUTest(8);
   ctECSRemoveUTest(32);

   for (uint32_t i = 0; i < ctECSItCountUTest(); i++) {
      ctVec3* v = ctECSItGetComponentUTest(i);
      ctEntity e = ctECSItGetEntityUTest(i);
      ctAssert(v);
      ctAssert(e != CT_ENTITY_INVALID);
      // ctDebugLog("E: %u XYZ: %f %f %f", (uint32_t)e, v->x, v->y, v->z);
   }
}

#else
void ctUnitTestECS() {
}
#endif