/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "SharedLogging.h"

void ctDebugLog(const char* format, ...) {
#if CT_IS_DEBUG || CT_BUILD_UNIT_TESTS
   va_list args;
   va_start(args, format);
   fprintf(stderr, "[INFO] ");
   vfprintf(stderr, format, args);
   fprintf(stderr, "\n");
#if CT_BUILD_UNIT_TESTS
   vfprintf(stdout, format, args);
   fprintf(stdout, "\n");
#endif
   va_end(args);
#endif
}

void ctDebugWarning(const char* format, ...) {
#if CT_IS_DEBUG
   va_list args;
   va_start(args, format);
   fprintf(stderr, "[WARNING] ");
   vfprintf(stderr, format, args);
#if CT_BUILD_UNIT_TESTS
   fprintf(stdout, "[WARNING] ");
   vfprintf(stdout, format, args);
   fprintf(stdout, "\n");
#endif
   va_end(args);
#endif
}

void ctDebugError(const char* format, ...) {
#if CT_IS_DEBUG
   va_list args;
   va_start(args, format);
   fprintf(stderr, "[ERROR] ");
   vfprintf(stderr, format, args);
#if CT_BUILD_UNIT_TESTS
   fprintf(stdout, "[ERROR] ");
   vfprintf(stdout, format, args);
   fprintf(stdout, "\n");
#endif
   va_end(args);
#endif
}