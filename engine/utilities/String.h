/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once
/*! @file String.h

UTF8 aware string library targeted at simple game use cases

This library differs from other string libraries in the fact that it treats
strings not as arrays of characters but rather command buffers which hold text rendering intent.
Strings share cultures with everyone and many progammers overlook this with ascii centric bias.
By treating bytes as characters you can mangle and break strings with text from other languages.
This library discourages byte manual manipulation as and provides simple ways of manipulating 
strings designed for common game usage. For safer string manipulation see UTF32 functions.
*/


#include "Common.h"
#include "thirdparty/utf8/utf8.h"

#include "codegen/engine/utilities/String.h.gen.h"

/* ------- Common ------- */

/*! @brief Get size of null-terminated string in bytes (including null terminator)
    @warning Bytes are not characters as they can consist of only parts of codepoints
 */
size_t ctStringByteSize(const char* string);

/*! @brief Get the amount of codepoints in a null terminated string (including null terminator) 
    @warning Codepoints are still not "characters" but text rendering commands
*/
size_t ctStringGetUnicodeCodepointCount(const char* string);

/*! @brief Ensure the text buffer ends in a null terminator 
*/
void ctStringEnsureNullTerminated(char* buffer, size_t bufferSize);

/*! @brief Ensure the text buffer is valid unicode (replaces garbage with ?) */
void ctStringEnsureUnicodeValid(char* buffer, size_t bufferSize);

/* ------- Comparison ------- */

/*! @brief Unicode aware lexographical comparison */
int ctStringCmp(const char* leftString, const char* rightString);

/*! @brief Check if two string's contents are the same */
#define ctStringEqual(_leftString, _rightString) \
(ctStringCmp(_leftString, _rightString) == 0)

/* ------- Case ------- */

/*! @brief Convert string text to upper case as applicable */
void ctStringToUpper(char* string);

/*! @brief Convert string text to lower case as applicable */
void ctStringToLower(char* string);

/* ------- String Creation ------- */

/*! @brief Clear existing bytes in a buffer holding a string */
void ctStringClear(char* buffer, size_t bufferSize);

/*! @brief Copy a source string into a target buffer */
void ctStringCopy(char* buffer, size_t bufferSize, const char* sourceString);

/*! @brief Fill a string buffer with text following the printf() format 

    See https://en.wikipedia.org/wiki/Printf#Format_specifier
*/
void ctStringFormat(char* buffer, size_t bufferSize, const char* format, ...);

/*! @brief Same as ctStringFormat() but lets you pass a manual va_list */
void ctStringFormatVArgs(char* buffer, size_t bufferSize, const char* format, va_list vargs);

/* ------- Unicode 32 Conversion ------- */

/*! @brief UTF8 to UTF32 

    Converts to UTF32. The UTF32 buffer can be (more) safely manipulated as an array without breaking codepoints.
    Remember that codepoints are still not character but text rendering commands. When writing text manipulation
    code keep in the back of your mind that there are languages that use multiple codepoints to define characters
    or can even change the direction which text is rendering. If you are unsure how your logic translates accross
    cultures try to comminucate with your translators to extensively bug test for your target languages. 

    @param outputBuffer assumed to be atleast inputBufferSize * 4
*/
void ctStringConvertToUtf32(int32_t* outputBuffer, size_t outputBufferSize, const char* inputBuffer, size_t inputBufferSize);

/*! @brief UTF32 to UTF8

    Return trip from ctStringConvertToUtf32()
*/
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

/*! @brief Sets the dest to a bool value if a conversion is possible */
enum ctResults ctStringToBool(const char* buffer, size_t bufferSize, bool* dest);

/*! @brief Sets the dest to a int8_t value if a conversion is possible */
enum ctResults ctStringToInt8(const char* buffer, size_t bufferSize, int8_t* dest);
/*! @brief Sets the dest to a uint8_t value if a conversion is possible */
enum ctResults ctStringToUInt8(const char* buffer, size_t bufferSize, uint8_t* dest);

/*! @brief Sets the dest to a int16_t value if a conversion is possible */
enum ctResults ctStringToInt16(const char* buffer, size_t bufferSize, int16_t* dest);
/*! @brief Sets the dest to a uint16_t value if a conversion is possible */
enum ctResults ctStringToUInt16(const char* buffer, size_t bufferSize, uint16_t* dest);

/*! @brief Sets the dest to a int32_t value if a conversion is possible */
enum ctResults ctStringToInt32(const char* buffer, size_t bufferSize, int32_t* dest);
/*! @brief Sets the dest to a uint32_t value if a conversion is possible */
enum ctResults ctStringToUInt32(const char* buffer, size_t bufferSize, uint32_t* dest);

/*! @brief Sets the dest to a int64_t value if a conversion is possible */
enum ctResults ctStringToInt64(const char* buffer, size_t bufferSize, int64_t* dest);
/*! @brief Sets the dest to a uint64_t value if a conversion is possible */
enum ctResults ctStringToUInt64(const char* buffer, size_t bufferSize, uint64_t* dest);

/*! @brief Sets the dest to a float value if a conversion is possible */
enum ctResults ctStringToFloat(const char* buffer, size_t bufferSize, float* dest);
/*! @brief Sets the dest to a double value if a conversion is possible */
enum ctResults ctStringToDouble(const char* buffer, size_t bufferSize, double* dest);
/*! @brief Sets the dest to a long double value if a conversion is possible */
enum ctResults ctStringToLongDouble(const char* buffer, size_t bufferSize, long double* dest);

/* ------- Hexidecimal Conversion ------- */

/*! @brief Encodes a buffer of bytes into a string of hexidecimal character */
void ctHexToBytes(uint8_t* byteBuffer, size_t byteBufferSize, const char* hexBuffer, size_t hexBufferSize);
/*! @brief Decodes a string of hexidecimal charactes into a buffer of bytes */
void ctBytesToHex(char* hexBuffer, size_t hexBufferSize, const uint8_t* byteBuffer, size_t byteBufferSize);