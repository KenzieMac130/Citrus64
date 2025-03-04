/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "engine/utilities/Utilities.h"

#include "Renderer.h"
#include "t3d/t3d.h"
#include "t3d/t3dmodel.h"

#include "codegen/engine/renderer/RendererInternal.h.gen.h"

typedef struct {
   T3DViewport t3dViewport;
   float aspectRatio;
   bool ortho;
   float scale;

   float far;
   float near;
   bool enabled;
} ctViewport;