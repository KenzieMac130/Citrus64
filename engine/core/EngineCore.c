/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Utilities.h"

#include "engine/core/EngineCore.h"

#include "engine/renderer/Renderer.h"

#include "codegen/engine/core/EngineCore.c.gen.h"

void ctEngineIgnite() {
   ctRendererStartup();
}

void ctEngineLoop() {
   while (1) {
      ctRendererRenderFrame();
   }
}

void ctEngineShutdown() {
   ctRendererShutdown();
}