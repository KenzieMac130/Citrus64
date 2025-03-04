/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "ResourceInternal.h"

#include "t3d/t3dmodel.h"
#include "engine/formats/mo/MO.h"

#include "codegen/engine/resource/Resource.c.gen.h"

ctHashTable gResourceHashTable;
ctHashTableKey gResourceKeys[CT_MAX_RESOURCES];
int32_t gResourceRefcount[CT_MAX_RESOURCES];
ctResource gResources[CT_MAX_RESOURCES];

char pathScratch[128];

bool ctPathExists(const char* path) {
   if (strncmp(path, "rom://", 6) == 0) {
      if (!dfs_rom_addr(path + 6)) { return false; }
   } else {
      ctAssert("unimplemented");
      return false;
   }
   return true;
}

/* ---------------- Raw Resource ---------------- */

ctResults ctResourceLoadBytes(ctResource* dest,
                              ctResourceType type,
                              const char* path,
                              const char* extension) {
   ctStringFormat(pathScratch, 128, "rom://%s%s", path, extension);
   dest->type = type;
   dest->data = NULL;
   dest->object = dest->data;
   dest->size = 0;

#if CT_ALLOW_MISSING_RESOURCES
   if (!ctPathExists(pathScratch)) {
      ctDebugError("FILE NOT FOUND %s", pathScratch);
      return CT_FAILURE_FILE_NOT_FOUND;
   }
#endif
   dest->data = asset_load(pathScratch, &dest->size);
   return CT_SUCCESS;
}

void ctResourceUnloadBytes(ctResource* dest) {
   free(dest->data);
}

/* ---------------- Library Resource ---------------- */

bool ctResourceTypeHasCode(ctResourceType type) {
   switch (type) {
      case CT_RESOURCE_MODULE:
      case CT_RESOURCE_SCRIPT: return true;
      default: return false;
   }
}

ctResults ctResourceLoadLibrary(ctResource* dest,
                                ctResourceType type,
                                const char* path,
                                bool local) {
   ctStringFormat(pathScratch, 128, "rom://%s%s", path, ".dso");
   dest->type = type;
   dest->size = 0;
   dest->data = NULL;
   dest->object = NULL;

#if CT_ALLOW_MISSING_RESOURCES
   if (!ctPathExists(pathScratch)) {
      ctDebugError("FILE NOT FOUND %s", pathScratch);
      return CT_FAILURE_FILE_NOT_FOUND;
   }
#endif
   dest->object = dlopen(dest->object, local ? RTLD_LOCAL : RTLD_GLOBAL);
   if (!dest->object) { return CT_FAILURE_CORRUPTED_CONTENTS; }
   void (*fnLoad)(void) = dlsym(dest->object, "void OnLibraryLoad(void)");
   if (fnLoad) { fnLoad(); }
   return CT_SUCCESS;
}

void ctResourceUnloadLibrary(ctResource* dest) {
   ctAssert(ctResourceTypeHasCode(dest->type));
   if (!dest->object) { return; }
   void (*fnUnload)(void) = dlsym(dest->object, "void OnLibraryUnload(void)");
   if (fnUnload) { fnUnload(); }
   dlclose(dest->object);
}

/*! @brief Get a symbol from a resource if possible */
ctResults ctResourceGetSymbol(ctResourceHandle handle, const char* symbol, void** out) {
   ctResource* resource = ctResourceHandleGet(handle);
   if (!resource) {
      *out = NULL;
      return CT_FAILURE_FILE_NOT_FOUND;
   }
   if (ctResourceTypeHasCode(resource->type)) {
      *out = NULL;
      return CT_FAILURE_TYPE_ERROR;
   }
   ctAssert(resource->object);
   *out = dlsym(resource->object, symbol);
   if (!out) { return CT_FAILURE_NOT_FOUND; }
   return CT_SUCCESS;
}

/* ---------------- Sprite ---------------- */

ctResults ctResourceLoadSprite(ctResource* dest, const char* path) {
   ctStringFormat(pathScratch, 128, "rom://%s%s", path, ".sprite");
   dest->type = CT_RESOURCE_SPRITE;
   dest->data = NULL;
   dest->size = 0;

#if CT_ALLOW_MISSING_RESOURCES
   if (!ctPathExists(pathScratch)) {
      ctDebugError("FILE NOT FOUND %s", pathScratch);
      return CT_FAILURE_FILE_NOT_FOUND;
   }
#endif
   dest->object = sprite_load(pathScratch);
   return CT_SUCCESS;
}

void ctResourceUnloadSprite(ctResource* dest) {
   ctAssert((size_t)dest->type == CT_RESOURCE_SPRITE);
   ctAssert(dest->object);
   sprite_free((sprite_t*)dest->object);
}

/* ---------------- T3D Model ---------------- */

ctResults ctResourceLoadModel(ctResource* dest, const char* path) {
   ctStringFormat(pathScratch, 128, "rom://%s%s", path, ".t3dm");
   dest->type = CT_RESOURCE_MODEL;
   dest->data = NULL;
   dest->size = 0;

#if CT_ALLOW_MISSING_RESOURCES
   if (!ctPathExists(pathScratch)) {
      ctDebugError("FILE NOT FOUND %s", pathScratch);
      return CT_FAILURE_FILE_NOT_FOUND;
   }
#endif
   dest->object = (void*)t3d_model_load(pathScratch);
   return CT_SUCCESS;
}

void ctResourceUnloadModel(ctResource* dest) {
   ctAssert((size_t)dest->type == CT_RESOURCE_MODEL);
   if (!dest->object) { return; }
   t3d_model_free((T3DModel*)dest->object);
}

/* ---------------- Translation ---------------- */

ctResults ctResourceLoadTranslation(ctResource* dest, const char* path) {
   CT_RETURN_FAIL(ctResourceLoadBytes(dest, CT_RESOURCE_TRANSLATION, path, ".mo"));
   CT_RETURN_FAIL_CLEAN(
     ctMOReaderCreate((ctMOReader**)&dest->object, dest->data, dest->size),
     ctResourceUnloadBytes(dest));
   return CT_SUCCESS;
}

void ctResourceUnloadTranslation(ctResource* dest) {
   ctAssert((size_t)dest->type == CT_RESOURCE_TRANSLATION);
   ctMOReaderFree((ctMOReader*)dest->object);
   ctResourceUnloadBytes(dest);
}

const char* ctResourceGetTextHashed(ctResourceHandle handle, uint32_t hash) {
   ctResource* resource = ctResourceHandleGet(handle);
   if (!resource) { return NULL; }
   if (resource->type != CT_RESOURCE_TRANSLATION) { return NULL; }
   if (resource->object == NULL) { return NULL; }
   const char* result = ctMOFindTranslationHashed((ctMOReader*)resource->object, hash);
   if (!result) { return NULL; }
   return result;
}

/* ---------------- Font ---------------- */

ctResults ctResourceLoadFont(ctResource* dest, const char* path) {
   CT_RETURN_FAIL(ctResourceLoadBytes(dest, CT_RESOURCE_FONT, path, ".font64"));
   dest->object = dest->data;
   return CT_SUCCESS;
}

void ctResourceUnloadFont(ctResource* dest) {
   ctResourceUnloadBytes(dest);
}

ctFont* ctResourceGetFont(ctResourceHandle handle) {
   ctResource* resource = ctResourceHandleGet(handle);
   if (!resource) { return NULL; }
   if (resource->type != CT_RESOURCE_FONT) { return NULL; }
   return (ctFont*)(resource->object);
}

/* ---------------- All Resources ---------------- */

ctResults ctResourceLoad(ctResource* dest, ctResourceType type, const char* path) {
   switch (type) {
      case CT_RESOURCE_RAW: return ctResourceLoadBytes(dest, CT_RESOURCE_RAW, path, "");
      case CT_RESOURCE_MODULE:
         return ctResourceLoadLibrary(dest, CT_RESOURCE_MODULE, path, false);
      case CT_RESOURCE_SCRIPT:
         return ctResourceLoadLibrary(dest, CT_RESOURCE_MODULE, path, true);
      case CT_RESOURCE_TRANSLATION: return ctResourceLoadTranslation(dest, path);
      case CT_RESOURCE_SPRITE: return ctResourceLoadSprite(dest, path);
      case CT_RESOURCE_FONT: return ctResourceLoadFont(dest, path);
      case CT_RESOURCE_MODEL: return ctResourceLoadModel(dest, path);
      default: return CT_FAILURE_INVALID_PARAMETER;
   }
}

void ctResourceUnload(ctResource* dest) {
   switch (dest->type) {
      case CT_RESOURCE_RAW: ctResourceUnloadBytes(dest); break;
      case CT_RESOURCE_MODULE: ctResourceUnloadLibrary(dest); break;
      case CT_RESOURCE_SCRIPT: ctResourceUnloadLibrary(dest); break;
      case CT_RESOURCE_TRANSLATION: ctResourceUnloadTranslation(dest); break;
      case CT_RESOURCE_SPRITE: ctResourceUnloadSprite(dest); break;
      case CT_RESOURCE_FONT: return ctResourceUnloadFont(dest); break;
      case CT_RESOURCE_MODEL: ctResourceUnloadModel(dest); break;
      default:
   }
}

void ctResourceRelease(ctResourceHandle resource) {
   if (resource == CT_RESOURCE_HANDLE_INVALID) { return; }
   ctAssert(resource <= CT_MAX_RESOURCES);
   ctAssert(gResourceRefcount[resource] > 0);
   gResourceRefcount[resource]--;
}

ctResource* ctResourceHandleGet(ctResourceHandle handle) {
   if (handle == CT_RESOURCE_HANDLE_INVALID) { return NULL; }
   ctAssert(handle < CT_MAX_RESOURCES);
   return &gResources[handle];
}

uint32_t ctResourceGetHash(ctResourceType type, const char* path) {
   ctAssert(path);
   ctAssert(type < 255);
   pathScratch[0] = type + 1;
   ctStringCopy(&pathScratch[1], 127, path);
   return ctXXHash32String(pathScratch);
}

ctResults
ctResourceGetOrLoad(ctResourceHandle* out, ctResourceType type, const char* path) {
   const uint32_t hash = ctResourceGetHash(type, path);
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

void ctResourceManagerGarbageCollect() {
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      if (gResourceRefcount[i] > 0) { continue; }
      ctResourceUnload(&gResources[i]);
      gResourceRefcount[i] = 0;
   }
}

void ctResourceManagerStartup() {
   gResourceHashTable = ctHashTableInit(CT_MAX_RESOURCES, gResourceKeys);
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      gResourceRefcount[i] = 0;
   }
}

void ctResourceManagerShutdown() {
   for (uint32_t i = 0; i < CT_MAX_RESOURCES; i++) {
      if (gResourceRefcount[i] <= 0) { continue; }
      ctResourceUnload(&gResources[i]);
   }
}