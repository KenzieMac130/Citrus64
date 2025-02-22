/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Translation.h

Translate text into other languages
*/

#include "engine/utilities/Utilities.h"

#include "codegen/engine/core/Translation.h.gen.h"

/*! @brief Get the translated text for the user's language
    @warning results may be invalid eventually, use immediately or make a copy
*/
#define ctGetText(_identifier) __CT_COMPILED_TRANSLATION_LOOKUP_##_tag

/*! @brief see ctGetText() for the user API */
const char* _ctGetText(uint32_t hash, const char* nativeText);

/*! @brief Set the base path of the translations to be loaded next frame
    @param basePath is expected to contain mo files for each language
*/
void ctTranslationSetBank(uint32_t bankIndex, const char* basePath);

/*! @brief Set the target language to be loaded next game update
    @param isoCode Format as follows: "(ISO 639-1)-(ISO 3166 A2)" (ex: "en-us")

    The translation system will attempt to load the region specific mo file
    in the target language first, if this fails it will just look for the
    language. Full RFC 4646 is not supported.
*/
void ctTranslationSetLanguage(const char* isoCode);

/*! @brief Get the actively loaded language */
const char* ctTranslationGetLanguage();

void ctTranslationStartup();
void ctTranslationUpdate();
void ctTranslationShutdown();