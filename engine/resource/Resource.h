/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Resource.h

Resource management system
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "engine/renderer/Renderer.h"

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

/*! @brief Indicates a null or invalid resource */
#define CT_RESOURCE_HANDLE_INVALID UINT16_MAX

/*! @brief Describes a reference to a resource */
typedef uint16_t ctResourceHandle;

/*! @brief Return a handle to a loaded resource */
CT_ENGINE_API ctResults ctResourceGetOrLoad(ctResourceHandle* out,
                                            ctResourceType type,
                                            const char* path);

/*! @brief Release a reference to this resource */
CT_ENGINE_API void ctResourceRelease(ctResourceHandle resource);

/*! @brief Add a reference to this resource (use this when copying handles) */
CT_ENGINE_API void ctResourceAddReference(ctResourceHandle resource);

/*! @brief Cleanup any released references immediately */
CT_ENGINE_API void ctResourceManagerGarbageCollect();

/*! @brief Test if a file path exists */
CT_ENGINE_API bool ctPathExists(const char* path);

/*! @brief Get a C symbol from a SCRIPT or MODULE resource
   @returns a pointer to the C symbol or NULL if not found/incompatible */
CT_ENGINE_API ctResults ctResourceGetSymbol(ctResourceHandle handle,
                                            const char* symbol,
                                            void** out);

/*! @brief Get text from a translation resource
   @returns const char to be copied immediately or NULL if not found/incompatible */
CT_ENGINE_API const char* ctResourceGetTextHashed(ctResourceHandle handle, uint32_t hash);

/*! @brief Get the font from a resource
   @returns the font of the resource or a default one */
CT_ENGINE_API ctFont* ctResourceGetFont(ctResourceHandle handle);

/*! @brief Get the sprite from a resource
   @returns the sprite of the resource or a default one */
CT_ENGINE_API ctSprite* ctResourceGetSprite(ctResourceHandle handle);

/*! @brief Get the model from a resource
   @returns the model of the resource or a default one */
CT_ENGINE_API ctModel* ctResourceGetModel(ctResourceHandle handle);

CT_ENGINE_API void ctResourceManagerStartup();
CT_ENGINE_API void ctResourceManagerShutdown();