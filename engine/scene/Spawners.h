/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Spawners.h

Handles spawning prefabs in the world
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/engine/scene/Spawners.h.gen.h"

typedef struct {
    float position[3];
    uint32_t prefabHash;
    uint16_t rotation[4];
    uint8_t params[8];
} ctSpawner;