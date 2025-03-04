/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Utilities.h"

#include "engine/core/EngineCore.h"

#include "engine/core/Translation.h"
#include "engine/resource/Resource.h"
#include "engine/renderer/Renderer.h"
#include "game/GameGlobal.h"

#include "codegen/engine/core/EngineCore.c.gen.h"

void ctEngineIgnite() {
   ctResourceManagerStartup();
   ctTranslationStartup();
   ctRendererStartup();
   OnGameStartup();
}

void ctEngineLoop() {
   while (1) {
      ctTranslationUpdate();
      ctRendererRenderFrame();
      ctResourceManagerGarbageCollect();
   }
}

void ctEngineShutdown() {
   OnGameShutdown();
   ctRendererShutdown();
   ctTranslationShutdown();
   ctResourceManagerShutdown();
}