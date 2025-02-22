/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "BuiltinComponents.h"

#include "codegen/engine/scene/BuiltinComponents.c.gen.h"

CT_DEFINE_ECS_FLAGS(PositionDirty);
CT_DEFINE_COMPONENT(Position, ctVec3, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_ECS_FLAGS(RotationScaleDirty);
CT_DEFINE_COMPONENT(RotationScale,
                    ctComponentRotationScale,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_ECS_FLAGS(RenderInterpolate);
CT_DEFINE_COMPONENT(LastPosition, ctVec3, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);
CT_DEFINE_COMPONENT(LastRotationScale,
                    ctComponentRotationScale,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_COMPONENT(HitShape,
                    ctComponentHitShape,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_COMPONENT(RenderMatrix, void*, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_COMPONENT(Renderer,
                    ctComponentRenderer,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_ECS_FLAGS(ModelUpdate);
CT_DEFINE_COMPONENT(Model, ctComponentModel, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_ECS_FLAGS(GroundPlaneUpdate);
CT_DEFINE_COMPONENT(GroundPlane,
                    ctComponentGroundPlane,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_COMPONENT(Effect, ctComponentEffect, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);

CT_DEFINE_ECS_FLAGS(LoadManaged);
CT_DEFINE_COMPONENT(LoadPriority, int8_t, CT_COMPONENT_MAX, CT_ECS_DESTRUCTOR_NONE);
CT_DEFINE_COMPONENT(Relationship,
                    ctComponentRelationship,
                    CT_COMPONENT_MAX,
                    CT_ECS_DESTRUCTOR_NONE);