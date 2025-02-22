/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Translation.h"
#include "engine/resource/Resource.h"

#include "codegen/engine/core/Translation.c.gen.h"

char gLanguage[8];
char gBankPaths[8][128];
ctResourceHandle gBanks[8];

const char* _ctGetText(uint32_t hash, const char* nativeText) {
   return nativeText;
}

void ctTranslationSetBank(uint32_t bankIndex, const char* basePath) {
   ctAssert(bankIndex < CT_MAX_TRANSLATION_BANKS);
}

void ctTranslationSetLanguage(const char* isoCode) {
   ctStringCopy(gLanguage, 16, isoCode);
}

const char* ctTranslationGetLanguage() {
   return gLanguage;
}

void ctTranslationStartup() {
   ctTranslationSetLanguage(CT_DEFAULT_LANGUAGE);
   memset(gBankPaths, 0, sizeof(gBankPaths));
   gBankPaths[7][2] = 3;
}

void ctTranslationUpdate() {
}

void ctTranslationShutdown() {
}