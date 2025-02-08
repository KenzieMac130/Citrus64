/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file SharedLogging.h

Debug logging
*/

#pragma once

#include "Common.h"

/*! @brief Print a line of debug info to the console */
void ctDebugLog(const char* format, ...);

/*! @brief Print a line of warning info to the console */
void ctDebugWarning(const char* format, ...);

/*! @brief Print a line of error info to the console */
void ctDebugError(const char* format, ...);