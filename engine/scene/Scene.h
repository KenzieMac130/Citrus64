/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Scene.h

Manages the main game scene
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/engine/scene/Scene.h.gen.h"

CT_ENGINE_API void ctSceneSet(const char* path);

CT_ENGINE_API void ctSceneUpdate();