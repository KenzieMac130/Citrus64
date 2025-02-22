/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "ModuleResource.h"
#include "codegen/engine/resource/ModuleResource.c.gen.h"

ctResults ctResourceLoadModule(ctResource* dest, const char* path, bool local) {
   dest->type = CT_RESOURCE_RAW;
   dest->size = 0;
   dest->data = NULL;
   dest->object = dlopen(dest->object, local ? RTLD_LOCAL : RTLD_GLOBAL);
   if (!dest->object) { return CT_FAILURE_FILE_NOT_FOUND; }
   void (*fnLoad)(void);
   if (ctErrorCheck(ctResourceModuleGetSymbol(dest, "ModuleOnLoad", (void**)&fnLoad))) {
      ctAssert(fnLoad);
      fnLoad();
   }
   return CT_SUCCESS;
}

void ctResourceUnloadModule(ctResource* dest) {
   if (dest->object) {
      void (*fnUnload)(void);
      if (ctErrorCheck(
            ctResourceModuleGetSymbol(dest, "ModuleOnUnload", (void**)&fnUnload))) {
         ctAssert(fnUnload);
         fnUnload();
      }
   }
   dlclose(dest->object);
}

ctResults ctResourceGetSymbol(ctResource* resource, const char* symbol, void** out) {
   *out = dlsym(resource->object, symbol);
   if (!out) { return CT_FAILURE_NOT_FOUND; }
   return CT_SUCCESS;
}