/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file ModuleResource.h

A resource that represents a gameplay module or script
*/

#pragma once

#include "engine/utilities/Utilities.h"
#include "Resource.h"

#include "codegen/engine/resource/ModuleResource.h.gen.h"

/*! @brief Get a pointer following the dlsym() conventions if possible */
ctResults ctResourceModuleGetSymbol(ctResource* resource, const char* symbol, void** out);