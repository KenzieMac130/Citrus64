/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include "Resource.h"

#include "codegen/engine/resource/ResourceInternal.h.gen.h"

typedef struct {
   ctResourceType type;
   int size;
   void* data;
   void* object;
} ctResource;

ctResource* ctResourceHandleGet(ctResourceHandle handle);