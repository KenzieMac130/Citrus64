/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "Hash.h"

#define XXH_STATIC_LINKING_ONLY
#define XXH_IMPLEMENTATION
#include "thirdparty/xxHash/xxhash.h"

#include "codegen/engine/utilities/Hash.c.gen.h"

uint32_t ctXXHash32Bytes(const void* buffer, size_t size) {
   return XXH32(buffer, size, 0);
}

uint32_t ctXXHash32String(const char* string) {
   return ctXXHash32Bytes(string, strlen(string));
}