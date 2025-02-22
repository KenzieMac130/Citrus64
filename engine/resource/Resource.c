/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "Resource.h"

#include "codegen/engine/resource/Resource.c.gen.h"

ctHashTable gResourceHashTable;
ctHashTableKey gResourceKeys[CT_MAX_RESOURCES];
int32_t gResourceRefcount[CT_MAX_RESOURCES];
ctResource gResources[CT_MAX_RESOURCES];

extern ctResults ctResourceLoadRaw(ctResource* dest, const char* path);
extern ctResults ctResourceLoadModule(ctResource* dest, const char* path, bool local);
extern ctResults ctResourceLoadTranslation(ctResource* dest, const char* path);
extern ctResults ctResourceLoadModel(ctResource* dest, const char* path);

extern void ctResourceUnloadRaw(ctResource* dest);
extern void ctResourceUnloadModule(ctResource* dest);
extern void ctResourceUnloadTranslation(ctResource* dest);
extern void ctResourceUnloadModel(ctResource* dest);

ctResults ctResourceLoad(ctResource* dest, ctResourceType type, const char* path) {
   switch (dest->type) {
      case CT_RESOURCE_RAW: return ctResourceLoadRaw(dest, path);
      case CT_RESOURCE_MODULE: return ctResourceLoadModule(dest, path, false);
      case CT_RESOURCE_SCRIPT: return ctResourceLoadModule(dest, path, true);
      case CT_RESOURCE_TRANSLATION: return ctResourceLoadTranslation(dest, path);
      case CT_RESOURCE_SPRITE: return ctResourceLoadRaw(dest, path);
      case CT_RESOURCE_MODEL: return ctResourceLoadModel(dest, path);
      default: return CT_FAILURE_INVALID_PARAMETER;
   }
}

void ctResourceUnload(ctResource* dest) {
   switch (dest->type) {
      case CT_RESOURCE_RAW: ctResourceUnloadRaw(dest); break;
      case CT_RESOURCE_MODULE: ctResourceUnloadModule(dest); break;
      case CT_RESOURCE_SCRIPT: ctResourceUnloadModule(dest); break;
      case CT_RESOURCE_TRANSLATION: ctResourceUnloadTranslation(dest); break;
      case CT_RESOURCE_SPRITE: ctResourceUnloadRaw(dest); break;
      case CT_RESOURCE_MODEL: ctResourceUnloadModel(dest); break;
      default:
   }
}

void ctResourceRelease(ctResourceHandle resource) {
   ctAssert(resource <= CT_MAX_RESOURCES);
   ctAssert(gResourceRefcount[resource] != INT32_MAX);
   ctAssert(gResourceRefcount[resource] > 0);
   gResourceRefcount[resource]--;
}

ctResults
ctResourceGetOrLoad(ctResourceHandle* out, ctResourceType type, const char* path) {
   const uint32_t hash = ctXXHash32String(path);
   uint32_t idx;
   *out = CT_RESOURCE_HANDLE_INVALID;
   if (ctErrorCheck(ctHashTableFindIdx(&gResourceHashTable, hash, &idx))) {
      CT_RETURN_FAIL(ctHashTableInsert(&gResourceHashTable, hash, &idx));
      CT_RETURN_FAIL(ctResourceLoad(&gResources[idx], type, path));
   }
   if (gResources[idx].type != type) { return CT_FAILURE_TYPE_ERROR; }
   gResourceRefcount[idx]++;
   *out = (ctResourceHandle)idx;
   return CT_SUCCESS;
}

void ctResourceGarbageCollect() {
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      if (gResourceRefcount[i] > 0) { continue; }
      ctResourceUnload(&gResources[i]);
      gResourceRefcount[i] = INT32_MAX;
   }
}

void ctResourceManagerStartup() {
   gResourceHashTable = ctHashTableInit(CT_MAX_RESOURCES, gResourceKeys);
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      gResourceRefcount[i] = INT32_MAX;
   }
}

void ctResourceManagerShutdown() {
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      if (gResourceRefcount[i] == INT32_MAX) { continue; }
      ctResourceUnload(&gResources[i]);
   }
}