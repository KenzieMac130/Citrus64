/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Renderer.h"
#include "RendererInternal.h"

#include "engine/scene/BuiltinComponents.h"

#include "codegen/engine/renderer/Renderer.c.gen.h"

/* todo: initialize, per viewport? */
bool gFogEnable;
float gFogMin;
float gFogMax;
color_t gFogColor;

color_t gAmbientColor;

/* ---------------------- Background ------------------------ */

ctResourceHandle gBackgroundModelHandle = CT_RESOURCE_HANDLE_INVALID;
T3DModel* gBackgroundModel;
T3DMat4FP gBackgroundMatrix; /* expected to be a unit matrix */

void ctRendererSetBackgroundModel(ctResourceHandle model) {
   if (gBackgroundModelHandle != CT_RESOURCE_HANDLE_INVALID) {
      ctResourceRelease(gBackgroundModelHandle);
   }
   gBackgroundModel = (T3DModel*)ctResourceGetModel(model);
   gBackgroundModelHandle = model;
   ctResourceAddReference(gBackgroundModelHandle);
}

/* ---------------------- Viewports ------------------------ */

ctRect ctRendererGetScreenRect() {
   return (ctRect) {{0.0f, 0.0f},
                    {(float)display_get_width(), (float)display_get_height()}};
}

ctViewport gViewports[CT_MAX_VIEWPORTS];

void ctRendererViewportRefresh(uint8_t index) {
   if (gViewports[index].scale <= 0.0f) { return; }
   if (gViewports[index].ortho) {
      ctRendererSetViewportOrthographic(index, gViewports[index].scale);
   } else {
      ctRendererSetViewportPerspective(index, gViewports[index].scale);
   }
}

void ctRendererSetViewportEnabled(uint8_t index, bool enable) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctViewport* viewport = &gViewports[index];
   viewport->enabled = enable;
}

void ctRendererSetViewportRect(uint8_t index, ctRect rect) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(rect.scale.x > 0);
   ctAssert(rect.scale.y > 0);
   ctViewport* viewport = &gViewports[index];
   t3d_viewport_set_area(&viewport->t3dViewport,
                         (int32_t)rect.pos.x,
                         (int32_t)rect.pos.y,
                         (int32_t)rect.scale.x,
                         (int32_t)rect.scale.y);
   viewport->aspectRatio = rect.scale.x / rect.scale.y;
   ctRendererViewportRefresh(index);
}

void ctRendererSetViewportCamera(uint8_t index, ctVec3 position, ctQuat rotation) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctViewport* viewport = &gViewports[index];
   fm_mat4_t matrix;
   fm_mat4_from_translation(&matrix, (const fm_vec3_t*)&position);
   fm_mat4_rotate(&matrix, (const fm_quat_t*)&rotation);
   fm_mat4_inverse(&matrix, &matrix);
   t3d_viewport_set_view_matrix(&viewport->t3dViewport, (const T3DMat4*)&matrix);
}

void ctRendererSetViewportPerspective(uint8_t index, float fovY) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(fovY > 0.0f);
   ctViewport* viewport = &gViewports[index];
   viewport->ortho = false;
   viewport->scale = fovY;
   t3d_viewport_set_perspective(&viewport->t3dViewport,
                                T3D_DEG_TO_RAD(fovY),
                                viewport->aspectRatio,
                                viewport->near,
                                viewport->far);
}

void ctRendererSetViewportOrthographic(uint8_t index, float scaleY) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(scaleY > 0.0f);
   ctViewport* viewport = &gViewports[index];
   viewport->ortho = true;
   viewport->scale = scaleY;
   t3d_viewport_set_ortho(&viewport->t3dViewport,
                          -scaleY * viewport->aspectRatio,
                          scaleY * viewport->aspectRatio,
                          -scaleY,
                          scaleY,
                          viewport->near,
                          viewport->far);
}

void ctRendererSetViewportClipDistance(uint8_t index, float near, float far) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(near > 0.0f);
   ctAssert(far > near);
   ctViewport* viewport = &gViewports[index];
   viewport->near = near;
   viewport->far = far;
   ctRendererViewportRefresh(index);
}

/* ----------------------------- Renderer Core ---------------------------------- */

void ctRendererStartup() {
   display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);
   t3d_init((T3DInitParams) {});

   /* Setup Viewports */
   for (int i = 0; i < CT_MAX_VIEWPORTS; i++) {
      gViewports[i].t3dViewport = t3d_viewport_create();
      gViewports[i].aspectRatio = 1.0f;
      ctRendererSetViewportClipDistance(i, CT_DEFAULT_CLIP_NEAR, CT_DEFAULT_CLIP_FAR);
      ctRendererSetViewportPerspective(i, CT_DEFAULT_FOV);
      ctRendererSetViewportCamera(i, ctVec3Zero(), ctQuatIdentity());
      ctRendererSetViewportEnabled(0, false);
   }
   ctRendererSetViewportEnabled(0, true);
   ctRendererSetViewportRect(0, ctRendererGetScreenRect());

   /* Setup Defaults */
   t3d_mat4fp_identity((T3DMat4FP*)UncachedAddr(&gBackgroundMatrix));
   gAmbientColor = RGBA32(255, 255, 255, 255);
   gFogColor = RGBA32(255, 255, 255, 255);
}

void ctRendererShutdown() {
   t3d_destroy();
   display_close();
}

void ctRendererRenderViewport(ctViewport* viewport) {
   /* setup view/proj */
   t3d_viewport_attach(&viewport->t3dViewport);
   rdpq_set_prim_color((color_t) {0xFF, 0xFF, 0xFF, 0xFF});

   /* setup fog */
   rdpq_mode_fog(RDPQ_FOG_STANDARD);
   rdpq_set_fog_color(gFogColor);
   t3d_fog_set_range(gFogMin, gFogMax);
   t3d_fog_set_enabled(gFogEnable);

   /* setup lighting */
   t3d_light_set_ambient(&gAmbientColor.r);
   t3d_light_set_count(0);

   /* draw background */
   if (gBackgroundModel) {
      /* culling */
      const T3DBvh* bvh = t3d_model_bvh_get(gBackgroundModel);
      if (bvh) { t3d_model_bvh_query_frustum(bvh, &viewport->t3dViewport.viewFrustum); }

      /* draw model */
      t3d_matrix_set(&gBackgroundMatrix, false);
      t3d_model_draw(gBackgroundModel);
   }

   /* draw entities */
   const uint32_t inflightFrame = 0;
   const uint32_t rendererCount = ctECSItCountRenderer();
   for (uint32_t i = 0; i < rendererCount; i++) {
      const ctComponentRenderer* renderer = ctECSItGetComponentRenderer(i);
      rspq_block_run(renderer->blocks[inflightFrame]);
   }

   /* draw blob shadows */

   /* render debug visualizers */
   // todo

   /* draw per-viewport ui */
   // todo...
}

void ctRendererRenderFrame() {
   /* update matrices */

   /* setup */
   rdpq_attach(display_get(), display_get_zbuf());
   t3d_frame_start();

   /* clear buffers */
#if CT_CLEAR_COLOR
   t3d_screen_clear_color(CT_DEFAULT_CLEAR_COLOR);
#endif
   t3d_screen_clear_depth();

   /* render viewports */
   for (int vp = 0; vp < CT_MAX_VIEWPORTS; vp++) {
      if (!gViewports[vp].enabled) { continue; }
      ctRendererRenderViewport(&gViewports[vp]);
   }

   /* render composite ui */

   /* render debug ui */

   /* present */
   rdpq_detach_show();
}