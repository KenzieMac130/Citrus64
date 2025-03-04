/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file EngineCore.h

Main engine startup, shutdown, and loop
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/engine/core/EngineCore.h.gen.h"

CT_ENGINE_API void ctEngineIgnite();
CT_ENGINE_API void ctEngineLoop();
CT_ENGINE_API void ctEngineShutdown();