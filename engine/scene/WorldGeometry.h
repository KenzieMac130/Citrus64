/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file WorldGeometry.h

Background geometry that can be rendered and colided with
*/

#include "engine/utilities/Utilities.h"

#include "resource/ModelResource.h"

#include "codegen/engine/scene/WorldGeometry.h.gen.h"

typedef struct {
   ctVec3 position;
   uint32_t flags;
   ct model;
} ctWorldGeometry;