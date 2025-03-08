/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "Scene.h"

#include "engine/resource/Resource.h"

#include "codegen/engine/scene/Scene.c.gen.h"

bool gWantsLoad;
char gScenePath[128];
ctResourceHandle gScene = CT_RESOURCE_HANDLE_INVALID;

void (*OnSceneSetup)();

void ctSceneSet(const char* path) {
   gWantsLoad = true;
   ctStringCopy(gScenePath, 128, path);
}

void ctSceneLoadUpdate() {
   if (gWantsLoad) {
      if (gScene != CT_RESOURCE_HANDLE_INVALID) {
         ctResourceRelease(gScene);
         ctResourceManagerGarbageCollect();
      }
      CT_PANIC_FAIL(ctResourceGetOrLoad(&gScene, CT_RESOURCE_SCRIPT, gScenePath),
                    "Failed to Load");
      CT_PANIC_FAIL(ctResourceGetSymbol(gScene, "OnSceneSetup", (void**)&OnSceneSetup),
                    "No scene setup found");
      OnSceneSetup();
      gWantsLoad = false;
   }
}