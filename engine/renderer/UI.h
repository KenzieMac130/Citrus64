/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file UI.h

UI Drawing Library
*/
#pragma once

#include "engine/utilities/Utilities.h"

#include "Renderer.h"

#include "codegen/engine/renderer/UI.h.gen.h"

/*! @brief Possible blending modes to use for drawin UI */
typedef enum {
   CT_UI_BLEND_NORMAL,   /*!< @brief Basic alpha blended single texturing */
   CT_UI_BLEND_FLAT,     /*!< @brief Flat colored alpha blended rectangles */
   CT_UI_BLEND_SDF_METER /*!< @brief (todo) */
} ctUIBlendMode;

/*! @brief Alignment possibilities for the user interface */
typedef enum {
   CT_UI_ALIGN_CENTER,
   CT_UI_ALIGN_TOP,
   CT_UI_ALIGN_BOTTOM,
   CT_UI_ALIGN_LEFT,
   CT_UI_ALIGN_RIGHT,
   CT_UI_ALIGN_TOP_LEFT,
   CT_UI_ALIGN_TOP_RIGHT,
   CT_UI_ALIGN_BOTTOM_LEFT,
   CT_UI_ALIGN_BOTTOM_RIGHT
} ctUIAlignment;

/*! @brief Contains the state of the UI function */
typedef struct ctUIContextInternal ctUIContext;

/* -------------------- Rects -------------------- */

/*! @brief Set the sprite to use for rendering rects
    @param region sets the UV region of the texture */
CT_ENGINE_API void ctUISetSprite(ctUIContext* ctx, ctSprite* sprite);

/*! @brief Set the sprites to use for rendering multi-textured blend modes
    @param sprite1 uploaded into TILE0
    @param sprite2 uploaded into TILE1 (should have same size of sprite1)
    @warning each sprite must take up at most 1/2 of TMEM so half the usual budget
*/
CT_ENGINE_API void
ctUISetSpriteMulti(ctUIContext* ctx, ctSprite* sprite1, ctSprite* sprite2);

/*! @brief Set the blend mode to use for rendering rects */
CT_ENGINE_API void ctUISetBlendMode(ctUIContext* ctx, ctUIBlendMode mode);

/*! @brief Set the color to tint the upcoming rect
    @note call after ctUISetBlendMode to ensure correct settings */
CT_ENGINE_API void ctUISetColor(ctUIContext* ctx, ctColorRGBA8 color);

/*! @brief Draw a rectangle containing a small sprite(s) that fits in TMEM */
CT_ENGINE_API void ctUIDrawRect(ctUIContext* ctx, const ctRect rect, const ctRect* uv);

/* -------------------- Large Sprites -------------------- */

/*! @brief Draw a whole sprite consisting of multiple tiles to the output

    This does not support blend modes and is an expensive operation avoid for
    small icons and use for only large elements like logos, or backgrounds.
    Use multiple calls to ctUIDrawRect with mirroring/stretching if feasible */
CT_ENGINE_API void
ctUIDrawLargeSprite(ctUIContext* ctx, sprite_t* sprite, const ctRect rect);

/* -------------------- Text -------------------- */

/*! @brief Set the default font for rendering text */
CT_ENGINE_API void ctUISetFont(ctUIContext* ctx, uint8_t fontIndex);

/*! @brief Set the default syle for rendering text */
CT_ENGINE_API void ctUISetTextStyle(ctUIContext* ctx, uint8_t styleIndex);

/*! @brief Set the text alignment */
CT_ENGINE_API void ctUISetTextAlignment(ctUIContext* ctx, ctUIAlignment alignment);

/*! @brief Set the wraping mode of text */
CT_ENGINE_API void ctUISetTextWrap(ctUIContext* ctx, bool wrap);

/*! @brief Draw text
    @param format follows printf spec but uses rdpq_text specific
    formatting features. You can set fonts with $xx and styles with ^xx
    where "xx" is the hexidecimal of the font or style index. To use
    stray $ or ^ use $$ and ^^ respectively (see rdpq_text_printn)
    @returns position of the bottom right corner of the text */
CT_ENGINE_API ctVec2 ctUIDrawText(ctUIContext* ctx,
                                  const ctVec2 position,
                                  const char* format,
                                  ...);

/*! @brief Draw a text box

    Similar to ctUIDrawText but supports drawing to a region
    Avoid using if you can just use ctUIDrawText as this is
    much more expensive and meant for multi-line dialogue boxes */
CT_ENGINE_API void
ctUIDrawTextBox(ctUIContext* ctx, const ctRect rect, const char* format, ...);

/* -------------------- UI Layout -------------------- */

/*! @brief Describes how to layout the user interface */
typedef struct {
   ctRect rect; /*!< active rect of the layout */

   uint16_t columns;
   uint16_t currentElement;
   float currentSpaceX;
   float currentSpaceY;
   float spacingX;
   float spacingY;
} ctUILayout;

/*! @brief Do a layout vertically
   @param spacing amount of spacing between elements (0: use next dimensions)
 */
CT_ENGINE_API ctUILayout ctUILayoutVertical(const ctRect rect, float spacing);

/*! @brief Do a layout sideways
   @param spacing amount of spacing between elements (0: use next dimensions)
 */
CT_ENGINE_API ctUILayout ctUILayoutHorizontal(const ctRect rect, float spacing);

/*! @brief Do a layout in a row/column manner
   @param columns amount of columns per rowm
   @param spacingX amount of X spacing between elements (0: use next dimensions)
   @param spacingY amount of Y spacing between elements (0: use next dimensions)
 */
CT_ENGINE_API ctUILayout ctUILayoutGrid(const ctRect rect,
                                        uint16_t columns,
                                        float spacingX,
                                        float spacingY);

/*! @brief Progress in the layout based on a rect region */
CT_ENGINE_API void ctUILayoutNextRect(ctUILayout* layout, const ctRect rect);

/*! @brief Progress in the layout based on a ctUIDrawText result */
CT_ENGINE_API void ctUILayoutNextText(ctUILayout* layout, const ctVec2 result);

/*! @brief Progress in the layout (assumes spacing is absolute) */
CT_ENGINE_API void ctUILayoutNext(ctUILayout* layout);

/* -------------------- Multi-Viewport -------------------- */

/*! @brief The index ctUIGetViewportIndex will return if we are
    rendering on-top of all viewports (outside of split-screen)
*/
#define CT_UI_VIEWPORT_COMPOSITE UINT8_MAX

/*! @brief Get the viewport index of the context */
CT_ENGINE_API uint8_t ctUIGetViewportIndex(ctUIContext* ctx);

CT_ENGINE_API ctRect ctUIGetViewportRect(ctUIContext* ctx, bool safeArea);

/*! @brief Get a rect  */
CT_ENGINE_API ctRect ctUIGetChildRect(ctUIContext* ctx,
                                      const ctRect parent,
                                      const ctRect child,
                                      ctUIAlignment alignment);

/*! @brief Get a rect in 2D space for the active viewport */
CT_ENGINE_API ctRect ctUIGetRect3D(ctUIContext* ctx,
                                   ctVec3 position,
                                   ctVec2 dimensions,
                                   ctUIAlignment alignment,
                                   bool* visible);