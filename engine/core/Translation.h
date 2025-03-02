/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Translation.h

Translate text into other languages
*/

#include "engine/utilities/Utilities.h"

#include "codegen/engine/core/Translation.h.gen.h"

/*! @brief Quickly get translated text using a message id
    @param _msgid the id of the message using alnum and _ */
#define CT_TEXT(_msgid) __CT_MSGID_GET_TEXT_##_msgid

/*! @brief Get the translated text for the user's language
    @warning results may be invalid eventually, use immediately or make a copy
*/
const char* ctGetText(const char* identifier);

/*! @brief Similar to ctGetText() but faster using results of CT_XXH32_STRING
 */
const char* ctGetTextHashed(uint32_t hash);

/*! @brief Set the base path of the translations to be loaded next frame
    @param basePath is expected to contain mo files for each language
*/
void ctTranslationSetBank(uint32_t bankIndex, const char* basePath);

/*! @brief Set the target language to be loaded next game update
    @param isoCode lower case "(ISO 639-1)-(ISO 3166 A2)" (ex: "en-us")

    The translation system will attempt to load the region specific mo file
    in the target language first, if this fails it will just look for the
    language. Full RFC 4646 is not supported.
*/
void ctTranslationSetLanguage(const char* isoCode);

/*! @brief Get the actively loaded language */
const char* ctTranslationGetLanguage();

/*! @brief Update the translation system
    @warning Any pointers to strings will be instantly invalid
*/
void ctTranslationUpdate();

void ctTranslationStartup();
void ctTranslationShutdown();