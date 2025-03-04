/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Settings.h

Settings
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "codegen/engine/core/Settings.h.gen.h"

/* -------------------- Accessibility -------------------- */

/*! @brief Types of color blindness */
typedef enum {
   CT_VISION_REGULAR,     /*!< Unaffected vision */
   CT_VISION_RED_GREEN,   /*!< Deuteranopia and Protanopia */
   CT_VISION_BLUE_YELLOW, /*!< Tritanopia */
   CT_VISION_MONOCHROME,  /*!< Achromatopsia */
   CT_VISION_COUNT
} ctSettingsColorVision;

/*! @brief Get if the user has a color impediment */
CT_ENGINE_API ctSettingsColorVision ctSettingsGetColorVision();

typedef enum {
   CT_UI_SCALE_SMALLER,
   CT_UI_SCALE_NORMAL,
   CT_UI_SCALE_LARGE,
   CT_UI_SCALE_VERY_LARGE,
   CT_UI_SCALE_COUNT
} ctSettingsUIScale;

/*! @brief Desired scale to be applied to the UI */
CT_ENGINE_API ctSettingsUIScale ctSettingsGetUIScale();

/*! @brief Priotitize readability over visuals */
CT_ENGINE_API bool ctSettingsIsHighContrast();