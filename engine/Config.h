/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

/* --------------- Limits --------------- */
#define CT_MAX_TRANSLATION_BANKS 8
#define CT_MAX_RESOURCES 751
#define CT_MAX_VIEWPORTS 4
#define CT_MAX_FONTS 16

/* --------------- Rendering ----------------- */
#define CT_DEFAULT_CLEAR_COLOR RGBA32(0, 255, 0, 255)
#define CT_DEFAULT_CLIP_NEAR 10.0f
#define CT_DEFAULT_CLIP_FAR 1000.0f
#define CT_DEFAULT_FOV 90.0f

/* --------------- Translation --------------- */
#define CT_DEFAULT_LANGUAGE              "en-us"
#define CT_DEFAULT_TRANSLATION "MISSING TEXT!!!"

#define CT_TRANSLATION_BANK_CORE 0
#define CT_TRANSLATION_BANK_GAME 1
#define CT_DEFAULT_TRANSLATION_BANK_CORE "core/text/core"
#define CT_DEFAULT_TRANSLATION_BANK_GAME "game/text/game"

/* --------------- Behavior --------------- */
#define CT_ALLOW_MISSING_RESOURCES 1
#define CT_CLEAR_COLOR 1
#define CT_ALLOW_MULTI_THREADING 0

/* Codegenerated includes here */
#include "codegen/BuildConfig.h"

#include "codegen/engine/Config.h.gen.h"