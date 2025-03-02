/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Renderer.h

Core render system
*/

#include "engine/utilities/Utilities.h"

#include "codegen/engine/renderer/Renderer.h.gen.h"

void ctRendererStartup();
void ctRendererShutdown();

void ctRendererRenderFrame();

ctRect ctRendererGetScreenRect();

void ctRendererSetViewportEnabled(uint8_t index, bool enable);
void ctRendererSetViewportRect(uint8_t index, ctRect rect);
void ctRendererSetViewportCamera(uint8_t index, ctVec3 position, ctQuat rotation);
void ctRendererSetViewportPerspective(uint8_t index, float fovY);
void ctRendererSetViewportOrthographic(uint8_t index, float scaleY);
void ctRendererSetViewportClipDistance(uint8_t index, float near, float far);