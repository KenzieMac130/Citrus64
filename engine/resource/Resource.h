/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Resource.h

Resource management system
*/

#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/engine/resource/Resource.h.gen.h"

/*! @brief Resource types */
typedef enum {
   CT_RESOURCE_RAW,         /*!< @brief Raw managed data*/
   CT_RESOURCE_MODULE,      /*!< @brief Game code */
   CT_RESOURCE_SCRIPT,      /*!< @brief Lightweight module effects, scene, audio, music */
   CT_RESOURCE_TRANSLATION, /*!< @brief MO file (don't use directly, see Translation.h) */
   CT_RESOURCE_SPRITE,      /*!< @brief Libdragon sprite */
   CT_RESOURCE_FONT,        /*!< @brief Libdragon font */
   CT_RESOURCE_MODEL,       /*!< @brief Tiny3D model */
} ctResourceType;

#define CT_RESOURCE_HANDLE_INVALID UINT16_MAX
typedef uint16_t ctResourceHandle;

void ctResourceManagerStartup();
void ctResourceManagerShutdown();

/*! @brief Return a handle to a loaded resource */
ctResults
ctResourceGetOrLoad(ctResourceHandle* out, ctResourceType type, const char* path);
void ctResourceRelease(ctResourceHandle resource);

void ctResourceManagerGarbageCollect();

bool ctPathExists(const char* path);

ctResults ctResourceGetSymbol(ctResourceHandle handle, const char* symbol, void** out);
int ctResourceGetFont(ctResourceHandle handle);
const char* ctResourceGetTextHashed(ctResourceHandle handle, uint32_t hash);