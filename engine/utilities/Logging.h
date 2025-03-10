/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Logging.h

Debug logging
*/

#pragma once

#include "Common.h"

#include "codegen/engine/utilities/Logging.h.gen.h"

/*! @brief Print a line of debug info to the console */
CT_ENGINE_API void ctDebugLog(const char* format, ...);

/*! @brief Print a line of warning info to the console */
CT_ENGINE_API void ctDebugWarning(const char* format, ...);

/*! @brief Print a line of error info to the console */
CT_ENGINE_API void ctDebugError(const char* format, ...);