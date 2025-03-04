/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file GameGlobal.h

Global functions for the entire game outside of modules
The game project owns this file
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/game/GameGlobal.h.gen.h"

/*! @brief Called after the engine is initialized */
void OnGameStartup();

/*! @brief Called before the engine is shutdown */
void OnGameShutdown();