/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "String.h"

#include "thirdparty/utf8/utf8.h"

#include "codegen/engine/utilities/String.c.gen.h"

size_t ctStringByteSize(const char* string) {
   ctAssert(string);
   return utf8size(string);
}

size_t ctStringGetUnicodeCodepointCount(const char* string) {
   ctAssert(string);
   return utf8len(string) + 1; /* include null terminator */
}

void ctStringEnsureNullTerminated(char* buffer, size_t bufferSize) {
   ctAssert(buffer);
   ctAssert(bufferSize > 0);
   buffer[bufferSize - 1] = '\0';
}

void ctStringEnsureUnicodeValid(char* buffer, size_t bufferSize) {
   ctAssert(buffer);
   ctAssert(bufferSize > 0);
   utf8makevalid(buffer, '?');
}

/* --------------------------------- Comparison --------------------------------- */

int ctStringCmp(const char* leftString, const char* rightString) {
   ctAssert(leftString);
   ctAssert(rightString);
   return utf8cmp(leftString, rightString);
}

/* --------------------------------- Codepoint --------------------------------- */

bool ctCodePointIsDigit(int32_t c) {
   return (c >= '0' && c <= '9');
}

bool ctCodePointIsAlpha(int32_t c) {
   return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool ctCodePointIsAlnum(int32_t c) {
   return (ctCodePointIsDigit(c) || ctCodePointIsAlpha(c));
}

bool ctCodePointIsUnicode(int32_t c) {
   return (c > 127 || c < 0);
}

bool ctCodePointIsAscii(int32_t c) {
   return (c <= 127 && c >= 0);
}

bool ctCodePointIsAlphaUnicode(int32_t c) {
   return (ctCodePointIsAlpha(c) || ctCodePointIsUnicode(c));
}

bool ctCodePointIsAlnumUnicode(int32_t c) {
   return (ctCodePointIsAlnum(c) || ctCodePointIsUnicode(c));
}

bool ctCodePointIsUpper(int32_t c) {
   return utf8isupper(c);
}

bool ctCodePointIsLower(int32_t c) {
   return utf8islower(c);
}

int32_t ctCodePointToUpper(int32_t c) {
   return utf8uprcodepoint(c);
}

int32_t ctCodePointToLower(int32_t c) {
   return utf8lwrcodepoint(c);
}

/* --------------------------------- Case --------------------------------- */

void ctStringToUpper(char* string) {
   ctAssert(string);
   utf8upr(string);
}

void ctStringToLower(char* string) {
   ctAssert(string);
   utf8lwr(string);
}

/* --------------------------------- Creation --------------------------------- */

void ctStringClear(char* buffer, size_t bufferSize) {
   ctAssert(buffer);
   ctAssert(bufferSize > 0);
   memset(buffer, 0, bufferSize);
}

void ctStringCopy(char* buffer, size_t bufferSize, const char* source) {
   ctAssert(buffer);
   ctAssert(source);
   ctAssert(bufferSize > 0);
   utf8ncpy(buffer, source, bufferSize);
}

void ctStringFormatVArgs(char* buffer,
                         size_t bufferSize,
                         const char* format,
                         va_list vargs) {
   ctAssert(buffer);
   ctAssert(bufferSize > 0);
   vsnprintf(buffer, bufferSize, format, vargs);
   buffer[bufferSize - 1] = '\0';
}

void ctStringFormat(char* buffer, size_t bufferSize, const char* format, ...) {
   va_list args;
   va_start(args, format);
   ctStringFormatVArgs(buffer, bufferSize, format, args);
   va_end(args);
}

/* -------------------------- Unicode 32 Conversion  ---------------------------- */

void ctStringConvertToUtf32(int32_t* outputBuffer,
                            size_t outputBufferSize,
                            const char* inputBuffer,
                            size_t inputBufferSize) {
   ctAssert(inputBuffer);
   ctAssert(inputBufferSize > 0);
   ctAssert(outputBuffer);
   ctAssert(outputBufferSize > 0);
   ctAssert(outputBufferSize >= inputBufferSize * 4);
   const utf8_int8_t* next = (const utf8_int8_t*)inputBuffer;
   do {
      next = (const utf8_int8_t*)utf8codepoint(next, outputBuffer);
      outputBuffer++;
   } while (next);
   outputBuffer[outputBufferSize - 1] = '\0';
}

void ctStringConvertFromUtf32(char* outputBuffer,
                              size_t outputBufferSize,
                              const int32_t* inputBuffer,
                              size_t inputBufferSize) {
   ctAssert(inputBuffer);
   ctAssert(inputBufferSize > 0);
   ctAssert(outputBuffer);
   ctAssert(outputBufferSize > 0);
   ctAssert(outputBufferSize >= inputBufferSize * 4);
}

/* --------------------------------- Type --------------------------------- */

#define STR_TO_TYPE(_TYPE)                                                               \
   double temp;                                                                          \
   CT_RETURN_FAIL(ctStringToDouble(buffer, bufferSize, &temp));                          \
   *result = (_TYPE)temp;                                                                \
   return CT_SUCCESS;

#define STR_TO_TYPE_HIGH(_TYPE)                                                          \
   long double temp;                                                                     \
   CT_RETURN_FAIL(ctStringToLongDouble(buffer, bufferSize, &temp));                      \
   *result = (_TYPE)temp;                                                                \
   return CT_SUCCESS;

ctResults ctStringToBool(const char* buffer, size_t bufferSize, bool* result) {
   ctAssert(result);
   ctAssert(buffer);
   if (!bufferSize) { bufferSize = strlen(buffer); }
   if (buffer[0] == 't' || buffer[0] == 'T') {
      return true;
   } else if (buffer[0] == 'f' || buffer[0] == 'F') {
      return false;
   } else {
      STR_TO_TYPE(bool);
   }
}

ctResults ctStringToInt8(const char* buffer, size_t bufferSize, int8_t* result) {
   ctAssert(result);
   STR_TO_TYPE(int8_t);
}

ctResults ctStringToUInt8(const char* buffer, size_t bufferSize, uint8_t* result) {
   ctAssert(result);
   STR_TO_TYPE(uint8_t);
}

ctResults ctStringToInt16(const char* buffer, size_t bufferSize, int16_t* result) {
   ctAssert(result);
   STR_TO_TYPE(int16_t);
}

ctResults ctStringToUInt16(const char* buffer, size_t bufferSize, uint16_t* result) {
   ctAssert(result);
   STR_TO_TYPE(uint16_t);
}

ctResults ctStringToInt32(const char* buffer, size_t bufferSize, int32_t* result) {
   ctAssert(result);
   STR_TO_TYPE(int32_t);
}
ctResults ctStringToUInt32(const char* buffer, size_t bufferSize, uint32_t* result) {
   ctAssert(result);
   STR_TO_TYPE(uint32_t);
}

ctResults ctStringToInt64(const char* buffer, size_t bufferSize, int64_t* result) {
   ctAssert(result);
   STR_TO_TYPE_HIGH(int64_t);
}
ctResults ctStringToUInt64(const char* buffer, size_t bufferSize, uint64_t* result) {
   ctAssert(result);
   STR_TO_TYPE_HIGH(uint64_t);
}

ctResults ctStringToDouble(const char* buffer, size_t bufferSize, double* result) {
   ctAssert(buffer);
   ctAssert(result);
   if (!bufferSize) { bufferSize = strlen(buffer); }
   if (bufferSize >= 64) { bufferSize = 63; }
   char tmp[64];
   memset(tmp, 0, 64);
   utf8ncpy(tmp, buffer, bufferSize);
   char* endPtr = NULL;
   double tmpResult = strtod(tmp, &endPtr);
   if (endPtr == tmp) { return CT_FAILURE_SYNTAX_ERROR; }
   *result = tmpResult;
   return CT_SUCCESS;
}

ctResults
ctStringToLongDouble(const char* buffer, size_t bufferSize, long double* result) {
   ctAssert(buffer);
   ctAssert(result);
   if (!bufferSize) { bufferSize = strlen(buffer); }
   if (bufferSize >= 64) { bufferSize = 63; }
   char tmp[64];
   memset(tmp, 0, 64);
   utf8ncpy(tmp, buffer, bufferSize);
   char* endPtr = NULL;
   long double tmpResult = strtold(tmp, &endPtr);
   if (endPtr == tmp) { return CT_FAILURE_SYNTAX_ERROR; }
   *result = tmpResult;
   return CT_SUCCESS;
}

/* --------------------------------- Hex --------------------------------- */

/* https://gist.github.com/xsleonard/7341172 */
void ctHexToBytes(uint8_t* byteBuffer,
                  size_t byteBufferSize,
                  const char* hexBuffer,
                  size_t hexBufferSize) {
   ctAssert(hexBuffer);
   ctAssert(byteBuffer);
   ctAssert(byteBufferSize >= hexBufferSize * 2);
   for (size_t i = 0, j = 0; j < byteBufferSize; i += 2, j++) {
      byteBuffer[j] =
        (hexBuffer[i] % 32 + 9) % 25 * 16 + (hexBuffer[i + 1] % 32 + 9) % 25;
   }
}

/* https://stackoverflow.com/questions/6357031/how-do-you-convert-a-byte-array-to-a-hexadecimal-string-in-c
 */
void ctBytesToHex(char* hexBuffer,
                  size_t hexBufferSize,
                  const uint8_t* byteBuffer,
                  size_t byteBufferSize) {
   ctAssert(hexBuffer);
   ctAssert(byteBuffer);
   ctAssert(byteBufferSize <= hexBufferSize * 2);
   const char table[] = "0123456789abcdef";
   for (; byteBufferSize > 0; --byteBufferSize) {
      unsigned char c = *byteBuffer++;
      *hexBuffer++ = table[c >> 4];
      *hexBuffer++ = table[c & 0x0f];
   }
}