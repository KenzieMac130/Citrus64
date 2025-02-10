/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Common.h

Boilerplate for all engine and game files
*/

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

/*! @brief Return Codes for the engine's runtime errors */
typedef enum {
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
} ctResults;

/*Debug*/
#ifdef NDEBUG
#define CT_IS_DEBUG 0
#else
#define CT_IS_DEBUG 1
#endif

/*! @brief Runtime Fatal Error Throwing */
#define ctAssert(e) assert(e)

/*! @brief Offline Compile-time Error Throwing */
#define ctStaticAssert(e) static_assert(e)

/*! @brief Checks if a ctResults was unsucessful */
#define ctErrorCheck(_msg) (_msg != CT_SUCCESS)

/*! @brief Raise a fatal error while the game is running */
#define ctFatalError(_MESSAGE) ctAssert(0 && _MESSAGE)

/*! @brief Raise a fatal error if a ctResults runtime error occured */
#define CT_PANIC_FAIL(_arg, _message)                                                    \
   {                                                                                     \
      if (_arg != CT_SUCCESS) { ctFatalError(_message); }                                \
   }

/*! @brief Raise a fatal error if a truth check failed */
#define CT_PANIC_UNTRUE(_arg, _message)                                                  \
   {                                                                                     \
      if (!_arg) { ctFatalError(_message); }                                             \
   }

/*! @brief Bubble up the ctResults error to the owning function */
#define CT_RETURN_FAIL(_arg)                                                             \
   {                                                                                     \
      ctResults __res = (_arg);                                                          \
      if (__res != CT_SUCCESS) { return __res; }                                         \
   }

/*! @brief Same as CT_RETURN_FAIL() but can do cleanup before exiting */
#define CT_RETURN_FAIL_CLEAN(_arg, _cleanup)                                             \
   {                                                                                     \
      ctResults __res = (_arg);                                                          \
      if (__res != CT_SUCCESS) {                                                         \
         _cleanup;                                                                       \
         return __res;                                                                   \
      }                                                                                  \
   }

/*! @brief Return a given value upon a ctResults error */
#define CT_RETURN_ON_FAIL(_arg, _result)                                                 \
   if ((_arg) != CT_SUCCESS) { return _result; }

/*! @brief Return a given value upon a truth check failure */
#define CT_RETURN_ON_UNTRUE(_arg, _result)                                               \
   if (!(_arg)) { return _result; }

#define CT_RETURN_ON_NULL(_arg, _code) CT_RETURN_ON_UNTRUE(_arg, _code)

/*C Helpers*/

/*! @brief Check if (f) bit was turned on in (v) bitmask */
#define ctCFlagCheck(v, f) ((v & f) == f)

/*! @brief move (v) byte pointer forward to satisfy (a) alignment */
#define ctAlign(v, a) ((v + (a - 1)) & -a)

#include "codegen/engine/utilities/Common.h.gen.h"