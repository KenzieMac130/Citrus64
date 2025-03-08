/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file BuiltinComponents.h

Built-in engine components for the ECS
*/
#pragma once

#define CT_ECS_API CT_ENGINE_API

#include "ECSCore.h"

#include "engine/resource/Resource.h"
#include "t3d/t3dmath.h"

#include "codegen/engine/scene/BuiltinComponents.h.gen.h"

typedef struct {
   ctQuat rotation;
   ctVec3 scale;
} ctComponentRotationScale;

typedef struct {
   ctEntity parent;
   ctEntity firstChild;
   ctEntity nextSibling;
} ctComponentRelationship;

typedef struct {
   ctVec3 positionCache;
   uint32_t data;
} ctComponentHitShape;

typedef struct {
   ctResourceHandle model;
   uint16_t flags;
} ctComponentModel;

typedef struct {
   rspq_block_t* blocks[CT_MAX_INFLIGHT_FRAMES];
   uint8_t flags[CT_MAX_INFLIGHT_FRAMES];
   bool _visibleCull;
} ctComponentRenderer;

typedef struct {
   T3DMat4FP frames[CT_MAX_INFLIGHT_FRAMES];
} ctComponentRenderMatrices;

typedef struct {
   char str[16];
} ctComponentDebugLabel;

typedef struct {
   uint8_t shadowSize;
} ctComponentShadowRenderer;

CT_DECLARE_ECS_FLAGS(PositionDirty);
CT_DECLARE_COMPONENT(Position, ctVec3);

CT_DECLARE_ECS_FLAGS(RotationScaleDirty);
CT_DECLARE_COMPONENT(RotationScale, ctComponentRotationScale);

CT_DECLARE_ECS_FLAGS(RenderInterpolate);
CT_DECLARE_COMPONENT(LastPosition, ctVec3);
CT_DECLARE_COMPONENT(LastRotationScale, ctComponentRotationScale);

CT_DECLARE_COMPONENT(HitShape, ctComponentHitShape);

CT_DECLARE_COMPONENT(RenderMatrix, ctComponentRenderMatrices);

CT_DECLARE_ECS_FLAGS(RendererDirty);
CT_DECLARE_COMPONENT(Renderer, ctComponentRenderer);

CT_DECLARE_COMPONENT(Shadows, ctComponentShadowRenderer);
CT_DECLARE_COMPONENT(ShadowMatrix, ctComponentRenderMatrices);

CT_DECLARE_COMPONENT(Model, ctComponentModel);

CT_DECLARE_ECS_FLAGS(LoadManaged);
CT_DECLARE_COMPONENT(LoadPriority, int8_t);
CT_DECLARE_COMPONENT(Relationship, ctComponentRelationship);
CT_DECLARE_COMPONENT(SpawnerIndex, uint16_t);

CT_DECLARE_COMPONENT(AudioHandle, uint16_t);
CT_DECLARE_COMPONENT(MeshCollisionHandle, uint16_t);
CT_DECLARE_COMPONENT(ZoneHandle, uint16_t);

CT_DECLARE_COMPONENT(DebugLabel, ctComponentDebugLabel);

#undef CT_ECS_API