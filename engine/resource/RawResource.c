/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "RawResource.h"
#include "codegen/engine/resource/RawResource.c.gen.h"

ctResults ctResourceLoadRaw(ctResource* dest, const char* path) {
   dest->type = CT_RESOURCE_RAW;
   dest->data = asset_load(path, &dest->size);
   dest->object = dest->data;
   if (!dest->data) { return CT_FAILURE_FILE_NOT_FOUND; }
   return CT_SUCCESS;
}

void ctResourceUnloadRaw(ctResource* dest) {
   free(dest->data);
}