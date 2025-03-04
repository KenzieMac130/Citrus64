/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "Scene.h"

#include "engine/resource/Resource.h"

#include "codegen/engine/scene/Scene.h.gen.h"

bool gWantsLoad;
char gScenePath[128];
ctResourceHandle gScene = CT_RESOURCE_HANDLE_INVALID;

void (*OnSceneSetup)();

void ctSceneSet(const char* path) {
   gWantsLoad = true;
   if (gScene != CT_RESOURCE_HANDLE_INVALID) {}
   ctResourceGetOrLoad(&gScene, CT_RESOURCE_SCRIPT, path);
}

void ctSceneUpdate() {
   if (gWantsLoad) {
      if (gScene != CT_RESOURCE_HANDLE_INVALID) {
         ctResourceRelease(gScene);
         ctResourceManagerGarbageCollect();
      }
      CT_PANIC_FAIL(ctResourceGetOrLoad(&gScene, CT_RESOURCE_SCRIPT, gScenePath),
                    "Failed to Load");
      CT_PANIC_FAIL(
        ctResourceGetSymbol(gScene, "void OnSceneSetup(void)", (void**)&OnSceneSetup),
        "Failed to Load");
      OnSceneSetup();
   }
}