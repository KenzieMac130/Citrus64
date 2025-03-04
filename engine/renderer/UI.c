/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "UI.h"

#include "codegen/engine/renderer/UI.c.gen.h"

typedef struct ctUIContextInternal {
    float pixelScaleX;
    uint16_t viewportCoords[4];
 
    uint16_t texCoords[4];
 
    rdpq_textparms_t textParams;
    uint8_t font;
 
    uint8_t viewport;
 
    bool dirtyBlendMode;
    ctUIBlendMode lastBlendMode;
    ctColorRGBA8 lastColor;
    ctSprite* lastSpriteT0;
    ctSprite* lastSpriteT1;
 } ctUIContext;