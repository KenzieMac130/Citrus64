/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file BuiltinComponents.h

Built-in engine components for the ECS
*/

#include "ECSCore.h"

#include "engine/resource/Resource.h"

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
   uint32_t flags;
} ctComponentModel;

typedef struct {
   void* skeleton;
} ctComponentSkeleton;

typedef struct {
   void* animationSimple;
} ctComponentAnimation;

typedef struct {
   ctVec3 position;
   ctVec3 normal;
} ctComponentGroundPlane;

typedef struct {
   ctResourceHandle* script;
   float timer;
   ctColorRGBA8 color;
} ctComponentEffect;

typedef struct {
   void* displayList;
   uint32_t flags;
} ctComponentRenderer;

CT_DECLARE_ECS_FLAGS(PositionDirty);
CT_DECLARE_COMPONENT(Position, ctVec3);

CT_DECLARE_ECS_FLAGS(RotationScaleDirty);
CT_DECLARE_COMPONENT(RotationScale, ctComponentRotationScale);

CT_DECLARE_ECS_FLAGS(RenderInterpolate);
CT_DECLARE_COMPONENT(LastPosition, ctVec3);
CT_DECLARE_COMPONENT(LastRotationScale, ctComponentRotationScale);

CT_DECLARE_COMPONENT(HitShape, ctComponentHitShape);

CT_DECLARE_COMPONENT(RenderMatrix, void*);

CT_DECLARE_COMPONENT(Renderer, ctComponentRenderer);

CT_DECLARE_ECS_FLAGS(ModelUpdate);
CT_DECLARE_COMPONENT(Model, ctComponentModel);

CT_DECLARE_ECS_FLAGS(GroundPlaneUpdate);
CT_DECLARE_COMPONENT(GroundPlane, ctComponentGroundPlane);

CT_DECLARE_COMPONENT(Effect, ctComponentEffect);

CT_DECLARE_ECS_FLAGS(LoadManaged);
CT_DECLARE_COMPONENT(LoadPriority, int8_t);
CT_DECLARE_COMPONENT(Relationship, ctComponentRelationship);
CT_DECLARE_COMPONENT(SpawnerIndex, uint16_t);

CT_DECLARE_COMPONENT(AudioHandle, uint16_t);
CT_DECLARE_COMPONENT(MeshCollisionHandle, uint16_t);
CT_DECLARE_COMPONENT(ZoneHandle, uint16_t);