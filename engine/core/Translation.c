/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Translation.h"
#include "engine/resource/Resource.h"

#include "codegen/engine/core/Translation.c.gen.h"

char gLanguageRegion[16];
char gLanguageOnly[16];

bool gBankReload[CT_MAX_TRANSLATION_BANKS];
char gBankPaths[CT_MAX_TRANSLATION_BANKS][128];
ctResourceHandle gBanks[CT_MAX_TRANSLATION_BANKS];

const char* ctGetTextHashed(uint32_t hash) {
   const char* result;
   for (uint32_t i = 0; i < CT_MAX_TRANSLATION_BANKS; i++) {
      if (gBanks[i] == CT_RESOURCE_HANDLE_INVALID) { continue; }
      result = ctResourceGetTextHashed(gBanks[i], hash);
      if (result) { return result; }
   }
   return CT_DEFAULT_TRANSLATION;
}

const char* ctGetText(const char* identifier) {
   return ctGetTextHashed(ctXXHash32String(identifier));
}

void ctTranslationSetBank(uint32_t bankIndex, const char* basePath) {
   ctAssert(bankIndex < CT_MAX_TRANSLATION_BANKS);
   ctAssert(ctStringByteSize(basePath) <= 128);
   ctStringCopy(gBankPaths[bankIndex], 128, basePath);
   gBankReload[bankIndex] = true;
}

void ctTranslationSetLanguage(const char* isoCode) {
   ctAssert(isoCode);
   ctAssert(ctStringByteSize(isoCode) <= 16);
   ctStringCopy(gLanguageRegion, 16, isoCode);
   memset(gLanguageOnly, 0, 16);
   for (int i = 0; i < 16; i++) {
      if (gLanguageRegion[i] == '-') { break; }
      gLanguageOnly[i] = gLanguageRegion[i];
   }
   for (int i = 0; i < CT_MAX_TRANSLATION_BANKS; i++) {
      gBankReload[i] = true;
   }
}

const char* ctTranslationGetLanguage() {
   return gLanguageRegion;
}

void ctTranslationStartup() {
   for (uint32_t i = 0; i < CT_MAX_TRANSLATION_BANKS; i++) {
      gBankReload[i] = false;
      gBanks[i] = CT_RESOURCE_HANDLE_INVALID;
   }
   ctTranslationSetLanguage(CT_DEFAULT_LANGUAGE);
   ctTranslationSetBank(CT_TRANSLATION_BANK_CORE, CT_DEFAULT_TRANSLATION_BANK_CORE);
   ctTranslationSetBank(CT_TRANSLATION_BANK_GAME, CT_DEFAULT_TRANSLATION_BANK_GAME);
   ctTranslationUpdate();
}

char languagePath[128];
void ctTranslationUpdate() {
   for (uint32_t i = 0; i < CT_MAX_TRANSLATION_BANKS; i++) {
      if (!gBankReload[i]) { continue; }
      gBankReload[i] = false;
      if (gBanks[i] != CT_RESOURCE_HANDLE_INVALID) { ctResourceRelease(gBanks[i]); }

      if (ctStringEqual(gBankPaths[i], "")) { continue; }

      /* check if the language + region exists otherwise just try to load language */
      ctStringFormat(languagePath, 128, "rom://%s-%s.mo", gBankPaths[i], gLanguageRegion);
      if (ctPathExists(languagePath)) {
         ctStringFormat(languagePath, 128, "%s-%s", gBankPaths[i], gLanguageRegion);
      } else {
         ctStringFormat(languagePath, 128, "%s-%s", gBankPaths[i], gLanguageOnly);
      }

      /* load the actual mo file */
      if (ctErrorCheck(
            ctResourceGetOrLoad(&gBanks[i], CT_RESOURCE_TRANSLATION, languagePath))) {
         ctDebugError(
           "FAILED TO LOAD MO FILE FOR %s IN %s", gLanguageRegion, gBankPaths[i]);
      }
   }
}

void ctTranslationShutdown() {
   for (uint32_t i = 0; i < CT_MAX_TRANSLATION_BANKS; i++) {
      ctResourceRelease(gBanks[i]);
   }
}