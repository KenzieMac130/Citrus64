/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Renderer.h

Core render system
*/
#pragma once

#include "engine/utilities/Utilities.h"

// todo: cyclic dependency, fix and replace uint16_t model
//#include "engine/resource/Resource.h"

#include "codegen/engine/renderer/Renderer.h.gen.h"

typedef sprite_t ctSprite;
typedef rdpq_font_t ctFont;
typedef struct T3DModel ctModel;

CT_ENGINE_API void ctRendererStartup();
CT_ENGINE_API void ctRendererShutdown();

CT_ENGINE_API void ctRendererRenderFrame();

CT_ENGINE_API ctRect ctRendererGetScreenRect();

CT_ENGINE_API void ctRendererSetBackgroundModel(uint16_t model);

CT_ENGINE_API void ctRendererSetViewportEnabled(uint8_t index, bool enable);
CT_ENGINE_API void ctRendererSetViewportRect(uint8_t index, ctRect rect);
CT_ENGINE_API void ctRendererSetViewportCamera(uint8_t index, ctVec3 position, ctQuat rotation);
CT_ENGINE_API void ctRendererSetViewportPerspective(uint8_t index, float fovY);
CT_ENGINE_API void ctRendererSetViewportOrthographic(uint8_t index, float scaleY);
CT_ENGINE_API void ctRendererSetViewportClipDistance(uint8_t index, float near, float far);