/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>

#include <libdragon.h>

#include "engine/Config.h"

/* Errors */
enum ctResults {
   CT_SUCCESS = 0,
   CT_FAILURE_UNKNOWN = -1,
   CT_FAILURE_OUT_OF_MEMORY = -2,
   CT_FAILURE_INVALID_PARAMETER = -3,
   CT_FAILURE_UNSUPPORTED_HARDWARE = -4,
   CT_FAILURE_UNKNOWN_FORMAT = -5,
   CT_FAILURE_OUT_OF_BOUNDS = -6,
   CT_FAILURE_PARSE_ERROR = -7,
   CT_FAILURE_DECOMPRESSION_ERROR = -8,
   CT_FAILURE_FILE_NOT_FOUND = -9,
   CT_FAILURE_INACCESSIBLE = -10,
   CT_FAILURE_DATA_DOES_NOT_EXIST = -11,
   CT_FAILURE_DUPLICATE_ENTRY = -12,
   CT_FAILURE_NOT_UPDATABLE = -13,
   CT_FAILURE_COULD_NOT_SHRINK = -14,
   CT_FAILURE_CORRUPTED_CONTENTS = -15,
   CT_FAILURE_DEPENDENCY_NOT_MET = -16,
   CT_FAILURE_MODULE_NOT_INITIALIZED = -17,
   CT_FAILURE_NOT_FOUND = -18,
   CT_FAILURE_SYNTAX_ERROR = -19,
   CT_FAILURE_RUNTIME_ERROR = -19,
   CT_FAILURE_TYPE_ERROR = -20,
   CT_FAILURE_NOT_FINISHED = -21,
   CT_FAILURE_SKIPPED = -22,
   CT_FAILURE_INCORRECT_VERSION = -23,
   CT_FAILURE_END_OF_STREAM = -24
};

/*Debug*/
#ifdef NDEBUG
#define CITRUS_IS_DEBUG 0
#else
#define CITRUS_IS_DEBUG 1
#endif

/*Assert*/
#define ctAssert(e) assert(e)

#define ctErrorCheck(_msg) (_msg != CT_SUCCESS)

#define ctFatalError(_MESSAGE) ctAssert(0 && _MESSAGE)

#define CT_PANIC_FAIL(_arg, _message)                                                    \
   {                                                                                     \
      if (_arg != CT_SUCCESS) { ctFatalError(_message); }                                \
   }

#define CT_PANIC_UNTRUE(_arg, _message)                                                  \
   {                                                                                     \
      if (!_arg) { ctFatalError(_message); }                                             \
   }

#define CT_RETURN_FAIL(_arg)                                                             \
   {                                                                                     \
      enum ctResults __res = (_arg);                                                     \
      if (__res != CT_SUCCESS) { return __res; }                                         \
   }

#define CT_RETURN_FAIL_CLEAN(_arg, _cleanup)                                             \
   {                                                                                     \
      enum ctResults __res = (_arg);                                                     \
      if (__res != CT_SUCCESS) {                                                         \
         _cleanup;                                                                       \
         return __res;                                                                   \
      }                                                                                  \
   }

#define CT_RETURN_ON_FAIL(_arg, _code)                                                   \
   if ((_arg) != CT_SUCCESS) { return _code; }

#define CT_RETURN_ON_UNTRUE(_arg, _code)                                                 \
   if (!(_arg)) { return _code; }

#define CT_RETURN_ON_NULL(_arg, _code) CT_RETURN_ON_UNTRUE(_arg, _code)

/*C Helpers*/
#define ctCFlagCheck(v, f)      ((v & f) == f)
#define ctAlign(v, a)           ((v + (a - 1)) & -a)

/*Include common c files*/
#include "SharedLogging.h"
#include "Memory.h"
#include "Math.h"
#include "String.h"