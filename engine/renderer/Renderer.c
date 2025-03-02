/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Renderer.h"

#include "t3d/t3d.h"

#include "codegen/engine/renderer/Renderer.c.gen.h"

ctRect ctRendererGetScreenRect() {
   return (ctRect) {{0.0f, 0.0f},
                    {(float)display_get_width(), (float)display_get_height()}};
}

/* ---------------------- Viewports ------------------------ */

typedef struct {
   T3DViewport t3dViewport;
   float aspectRatio;
   bool ortho;
   float scale;

   float far;
   float near;
   bool enabled;
} ctViewport;

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
   gViewports[index].enabled = enable;
}

void ctRendererSetViewportRect(uint8_t index, ctRect rect) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(rect.scale.x > 0);
   ctAssert(rect.scale.y > 0);
   t3d_viewport_set_area(&gViewports[index].t3dViewport,
                         (int32_t)rect.pos.x,
                         (int32_t)rect.pos.y,
                         (int32_t)rect.scale.x,
                         (int32_t)rect.scale.y);
   gViewports[index].aspectRatio = rect.scale.x / rect.scale.y;
   ctRendererViewportRefresh(index);
}

void ctRendererSetViewportCamera(uint8_t index, ctVec3 position, ctQuat rotation) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   fm_mat4_t matrix;
   fm_mat4_from_translation(&matrix, (const fm_vec3_t*)&position);
   fm_mat4_rotate(&matrix, (const fm_quat_t*)&rotation);
   fm_mat4_inverse(&matrix, &matrix);
   t3d_viewport_set_view_matrix(&gViewports[index].t3dViewport, (const T3DMat4*)&matrix);
}

void ctRendererSetViewportPerspective(uint8_t index, float fovY) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(fovY > 0.0f);
   gViewports[index].ortho = false;
   gViewports[index].scale = fovY;
   t3d_viewport_set_perspective(&gViewports[index].t3dViewport,
                                T3D_DEG_TO_RAD(fovY),
                                gViewports[index].aspectRatio,
                                gViewports[index].near,
                                gViewports[index].far);
}

void ctRendererSetViewportOrthographic(uint8_t index, float scaleY) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(scaleY > 0.0f);
   gViewports[index].ortho = true;
   gViewports[index].scale = scaleY;
   t3d_viewport_set_ortho(&gViewports[index].t3dViewport,
                          -scaleY * gViewports[index].aspectRatio,
                          scaleY * gViewports[index].aspectRatio,
                          -scaleY,
                          scaleY,
                          gViewports[index].near,
                          gViewports[index].far);
}

void ctRendererSetViewportClipDistance(uint8_t index, float near, float far) {
   ctAssert(index < CT_MAX_VIEWPORTS);
   ctAssert(near > 0.0f);
   ctAssert(far > near);
   gViewports[index].near = near;
   gViewports[index].far = far;
   ctRendererViewportRefresh(index);
}

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
}

void ctRendererShutdown() {
   t3d_destroy();
   display_close();
}

void ctRendererRenderFrame() {
   rdpq_attach(display_get(), display_get_zbuf());
   t3d_frame_start();

#if CT_CLEAR_COLOR
   t3d_screen_clear_color(CT_DEFAULT_CLEAR_COLOR);
#endif
   t3d_screen_clear_depth();

   for (int vp = 0; vp < CT_MAX_VIEWPORTS; vp++) {
      if (!gViewports[vp].enabled) { continue; }
      t3d_viewport_attach(&gViewports[vp].t3dViewport);
      /* todo: render viewport */
   }

   rdpq_detach_show();
}