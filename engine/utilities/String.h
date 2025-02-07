/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "Common.h"
#include "thirdparty/utf8/utf8.h"

/*
Assumes strings will always know their buffer size and be null terminated
*/

/* ------- Common ------- */

size_t ctStringByteSize(const char* string);
size_t ctStringGetUnicodeCodepointCount(const char* string);

void ctStringEnsureNullTerminated(char* buffer, size_t bufferSize);
void ctStringEnsureUnicodeValid(char* buffer, size_t bufferSize);

/* ------- Comparison ------- */

int ctStringCmp(const char* leftString, const char* rightString);

#define ctStringEqual(_leftString, _rightString) \
(ctStringCmp(_leftString, _rightString) == 0)

/* ------- Case ------- */

void ctStringToUpper(char* buffer, size_t bufferSize);
void ctStringToLower(char* buffer, size_t bufferSize);

/* ------- String Creation ------- */

void ctStringClear(char* buffer, size_t bufferSize);
void ctStringCopy(char* buffer, size_t bufferSize, const char* sourceString);
void ctStringFormat(char* buffer, size_t bufferSize, const char* format, ...);
void ctStringFormatVArgs(char* buffer, size_t bufferSize, const char* format, va_list vargs);

/* ------- Unicode 32 Conversion ------- */

void ctStringConvertToUtf32(int32_t* outputBuffer, size_t outputBufferSize, const char* inputBuffer, size_t inputBufferSize);
void ctStringConvertFromUtf32(char* outputBuffer, size_t outputBufferSize, const int32_t* inputBuffer, size_t inputBufferSize);

/* ------- Codepoint ------- */

#define ctCodePointIsDigit(c) (c >= '0' && c <= '9')
#define ctCodePointIsAlpha(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
#define ctCodePointIsAlnum(c) (ctIsDigit(c) || ctIsAlpha(c))
#define ctCodePointIsUnicode(c) (c > 127 || c < 0)
#define ctCodePointIsAscii(c) (c <= 127 && c >= 0)
#define ctCodePointIsAlphaUnicode(c) (ctIsAlpha(c) || ctIsUnicode(c))
#define ctCodePointIsAlnumUnicode(c) (ctIsAlnum(c) || ctIsUnicode(c))
#define ctCodePointIsUpper(c) utf8isupper(c)
#define ctCodePointIsLower(c) utf8islower(c)
#define ctCodePointToUpper(c) utf8uprcodepoint(c)
#define ctCodePointToLower(c) utf8lwrcodepoint(c)

/* ------- String to Type Conversion ------- */

enum ctResults ctStringToBool(const char* buffer, size_t bufferSize, bool* result);

enum ctResults ctStringToInt8(const char* buffer, size_t bufferSize, int8_t* result);
enum ctResults ctStringToUInt8(const char* buffer, size_t bufferSize, uint8_t* result);

enum ctResults ctStringToInt16(const char* buffer, size_t bufferSize, int16_t* result);
enum ctResults ctStringToUInt16(const char* buffer, size_t bufferSize, uint16_t* result);

enum ctResults ctStringToInt32(const char* buffer, size_t bufferSize, int32_t* result);
enum ctResults ctStringToUInt32(const char* buffer, size_t bufferSize, uint32_t* result);

enum ctResults ctStringToInt64(const char* buffer, size_t bufferSize, int64_t* result);
enum ctResults ctStringToUInt64(const char* buffer, size_t bufferSize, uint64_t* result);

enum ctResults ctStringToFloat(const char* buffer, size_t bufferSize, float* result);
enum ctResults ctStringToDouble(const char* buffer, size_t bufferSize, double* result);
enum ctResults ctStringToLongDouble(const char* buffer, size_t bufferSize, long double* result);

/* ------- Hexidecimal Conversion ------- */

void ctHexToBytes(uint8_t* byteBuffer, size_t byteBufferSize, const char* hexBuffer, size_t hexBufferSize);
void ctBytesToHex(char* hexBuffer, size_t hexBufferSize, const uint8_t* byteBuffer, size_t byteBufferSize);