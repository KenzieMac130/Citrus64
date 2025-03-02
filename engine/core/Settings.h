/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Settings.h

Settings
*/

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
ctSettingsColorVision ctSettingsGetColorVision();

typedef enum {
   CT_UI_SCALE_SMALLER,
   CT_UI_SCALE_NORMAL,
   CT_UI_SCALE_LARGE,
   CT_UI_SCALE_VERY_LARGE,
   CT_UI_SCALE_COUNT
} ctSettingsUIScale;

/*! @brief Desired scale to be applied to the UI */
ctSettingsUIScale ctSettingsGetUIScale();

/*! @brief Priotitize readability over visuals */
bool ctSettingsIsHighContrast();