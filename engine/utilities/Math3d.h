/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once
/*! @file Math3d.h

Math functions for working with 3D space
*/

#include "Common.h"

/* ------- Vector3 -------*/

/* Hard-coded coordinate spaces (based on glTF) */
// clang-format off
#define CT_UP           0.0f,  1.0f,  0.0f    
#define CT_DOWN         0.0f, -1.0f,  0.0f   
#define CT_FORWARD      0.0f,  0.0f,  1.0f   
#define CT_BACK         0.0f,  0.0f, -1.0f    
#define CT_RIGHT       -1.0f,  0.0f,  0.0f   
#define CT_LEFT         1.0f,  0.0f,  0.0f
// clang-format on
#define CT_VEC3_UP      (ctVec3){CT_UP}
#define CT_VEC3_DOWN    (ctVec3){CT_DOWN}
#define CT_VEC3_FORWARD (ctVec3){CT_FORWARD}
#define CT_VEC3_BACK    (ctVec3){CT_BACK}
#define CT_VEC3_RIGHT   (ctVec3){CT_RIGHT}
#define CT_VEC3_LEFT    (ctVec3){CT_LEFT}

typedef struct {
    float x;
    float y;
    float z;
} __attribute__((aligned(16))) ctVec3;

inline ctVec3 ctVec3Zero() {
    return (ctVec3){0.0f, 0.0f, 0.0f};
}

inline ctVec3 ctVec3Make(float x, float y, float z) {
    return (ctVec3){x, y, z};
}

inline ctVec3 ctVec3Identity() {
    return (ctVec3){1.0f, 1.0f, 1.0f};
}

inline ctVec3 ctVec3FromFloat3(const float data[3]) {
    ctAssert(data);
    return (ctVec3){data[0], data[1], data[2]};
}

inline ctVec3 ctVec3FromFloat(float value) {
    return (ctVec3){value, value, value};
}

inline bool ctVec3ApproxEqual(const ctVec3 a, const ctVec3 b) {
    return ctMultiFloatCompare(3, (float*)&a, (float*)&b, 0.0001f);
}

inline void ctVec3Add(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

inline void ctVec3Sub(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

inline void ctVec3Negate(ctVec3* v) {
    ctAssert(v);
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

inline void ctVec3Mult(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

inline void ctVec3Scale(ctVec3* a, const float b) {
    ctAssert(a);
    a->x *= b;
    a->y *= b;
    a->z *= b;
}

inline void ctVec3Divide(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
}

inline void ctVec3DivideFloat(ctVec3* a, const float b) {
    ctAssert(a);
    a->x /= b;
    a->y /= b;
    a->z /= b;
}

inline float ctVec3Dot(const ctVec3 a, const ctVec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float ctVec3Distance(const ctVec3 a, const ctVec3 b) {
    return ctSqrtf(ctPowf(a.x - b.x, 2.0f) + ctPowf(a.y - b.y, 2.0f) +
                   ctPowf(a.z - b.z, 2.0f));
}

inline float ctVec3Length(const ctVec3 v) {
    return ctSqrtf(ctVec3Dot(v, v));
}

inline void ctVec3Abs(ctVec3* v) {
    ctAssert(v);
    v->x = ctAbsf(v->x);
    v->y = ctAbsf(v->y);
    v->z = ctAbsf(v->z);
}

inline void ctVec3Normalize(ctVec3* v) {
    ctAssert(v);
    ctVec3DivideFloat(v, ctVec3Length(*v));
}

inline void ctVec3Saturate(ctVec3* v) {
    ctAssert(v);
    v->x = ctSaturatef(v->x);
    v->y = ctSaturatef(v->y);
    v->z = ctSaturatef(v->z);
}

inline void ctVec3Cross(ctVec3* out, const ctVec3 a, const ctVec3 b) {
    ctAssert(out);
    out->x = a.y * b.z - b.y * a.z;
    out->y = a.z * b.x - b.z * a.x;
    out->z = a.x * b.y - b.x * a.y;
}

inline void ctVec3Lerp(ctVec3* out, const ctVec3 a, const ctVec3 b, const float t) {
    ctAssert(out);
    out->x = ctLerpf(a.x, b.x, t);
    out->y = ctLerpf(a.y, b.y, t);
    out->z = ctLerpf(a.z, b.z, t);
}

/* ------- Quaternion -------*/

typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) ctQuat;

inline ctQuat ctQuatIdentity() {
    return (ctQuat){0.0f, 0.0f, 0.0f, 1.0f};
}
inline ctQuat ctQuatFromFloat4(const float v[4]) {
    return (ctQuat){v[0], v[1], v[2], v[3]};
}

inline ctQuat ctQuatFromAxisAngle(const ctVec3 axis, float angle) {
    /* https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm */
    ctQuat result;
    float sin;
    float cos;
    ctSinCosf(angle * 0.5f, &sin, &cos);
    result.x = axis.x * sin;
    result.y = axis.y * sin;
    result.z = axis.z * sin;
    result.w = cos;
    return result;
}

inline ctQuat ctQuatFromEuler(const ctVec3 euler) {
/* https://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm */
    // Assuming the angles are in radians.
      float c1, s1, c2, s2, c3, s3;
      ctSinCosf(euler.y * 0.5f, &s1, &c1);
      ctSinCosf(euler.z * 0.5f, &s2, &c2);
      ctSinCosf(-euler.x * 0.5f, &s3, &c3);

      const float c1c2 = c1*c2;
      const float s1s2 = s1*s2;

      ctQuat result;
      result.x =c1c2*s3 + s1s2*c3;
      result.y =s1*c2*c3 + c1*s2*s3;
      result.z =c1*s2*c3 - s1*c2*s3;
      result.w =c1c2*c3 - s1s2*s3;
      return result;
}

inline void ctQuatRotate(ctQuat* a, const ctQuat b) {
    ctQuat result;
    result.x = a->w * b.x + a->x * b.w + a->y * b.z - a->z * b.y;
    result.y = a->w * b.y - a->x * b.z + a->y * b.w + a->z * b.x;
    result.z = a->w * b.z + a->x * b.y - a->y * b.x + a->z * b.w;
    result.w = a->w * b.w - a->x * b.x - a->y * b.y - a->z - b.z;
    *a = result;
}

inline void ctQuatInvert(ctQuat* v) {
    /* todo */
}

inline void ctQuatNormalize(ctQuat* v) {
    /* https://www.cprogramming.com/tutorial/3d/quaternions.html */
    const float ilen = ctInvSqrtf(ctPowf(v->x, 2.0f) + ctPowf(v->y, 2.0f) +
                   ctPowf(v->z, 2.0f) + ctPowf(v->w, 2.0f));
    if(ilen <= 0.0f){
        *v = ctQuatIdentity();
        return;
    }
    v->x *= ilen;
    v->y *= ilen;
    v->z *= ilen;
    v->w *= ilen;
}

inline void ctQuatRotateVec3(ctVec3* vector, const ctQuat q) {
    /* logic borrowed from cglm */
    ctVec3 u, v1, v2;
    float s;
  
    u = ctVec3Make(q.x, q.y, q.z);
    s = q.w;
  
    v1 = u;
    v2 = *vector;
    ctVec3Scale(&v1, 2.0f * ctVec3Dot(u, *vector));
    ctVec3Scale(&v2, s * s - ctVec3Dot(u, u));
    ctVec3Add(&v1, v2);
  
    ctVec3Cross(&v2, u, *vector);
    ctVec3Scale(&v2, 2.0f * s);
  
    *vector = v1;
    ctVec3Add(vector, v2);
}

inline ctVec3 ctQuatGetForward(const ctQuat q) {
    ctVec3 axis = CT_VEC3_FORWARD;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctVec3 ctQuatGetBack(const ctQuat q) {
    ctVec3 axis = CT_VEC3_BACK;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctVec3 ctQuatGetUp(const ctQuat q) {
    ctVec3 axis = CT_VEC3_UP;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctVec3 ctQuatGetDown(const ctQuat q) {
    ctVec3 axis = CT_VEC3_DOWN;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctVec3 ctQuatGetRight(const ctQuat q) {
    ctVec3 axis = CT_VEC3_RIGHT;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctVec3 ctQuatGetLeft(const ctQuat q) {
    ctVec3 axis = CT_VEC3_LEFT;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

inline ctQuat ctQuatLookAt(const ctVec3 direction, const ctVec3 forward, const ctVec3 up) {
// ctQuat result;
// glm_quat_for((float*)dir.data, (float*)fwd.data, (float*)up.data, (float*)result.data);
// return result;
}

inline void ctQuatSlerp(ctQuat* a, const ctQuat b, float t) {
    //float cosTheta, sinTheta, angle;
    /* https://github.com/recp/cglm/blob/master/include/cglm/quat.h#L321 */
}

/* ------- Color -------*/

enum ctColorComponents {
    CT_COLOR_COMPONENT_NONE = 0x00,
    CT_COLOR_COMPONENT_R = 0x01,
    CT_COLOR_COMPONENT_G = 0x02,
    CT_COLOR_COMPONENT_B = 0x04,
    CT_COLOR_COMPONENT_A = 0x08,
    CT_COLOR_COMPONENT_RG = CT_COLOR_COMPONENT_R | CT_COLOR_COMPONENT_G,
    CT_COLOR_COMPONENT_RGB = CT_COLOR_COMPONENT_RG | CT_COLOR_COMPONENT_B,
    CT_COLOR_COMPONENT_RGBA = CT_COLOR_COMPONENT_RGB | CT_COLOR_COMPONENT_A,
};
 
#define CT_COLOR_BLACK           (ctColorRGBA8){000, 000, 000, 255}
#define CT_COLOR_GREY            (ctColorRGBA8){127, 127, 127, 255}
#define CT_COLOR_WHITE           (ctColorRGBA8){255, 255, 255, 255}
#define CT_COLOR_INVISIBLE_BLACK (ctColorRGBA8){000, 000, 000, 000}
#define CT_COLOR_INVISIBLE_GREY  (ctColorRGBA8){127, 127, 127, 000}
#define CT_COLOR_INVISIBLE_WHITE (ctColorRGBA8){255, 255, 255, 000}
#define CT_COLOR_RED             (ctColorRGBA8){255, 000, 000, 255}
#define CT_COLOR_GREEN           (ctColorRGBA8){000, 255, 000, 255}
#define CT_COLOR_BLUE            (ctColorRGBA8){000, 000, 255, 255}
#define CT_COLOR_YELLOW          (ctColorRGBA8){255, 255, 000, 255}
#define CT_COLOR_ORANGE          (ctColorRGBA8){255, 127, 000, 255}
#define CT_COLOR_PURPLE          (ctColorRGBA8){127, 000, 255, 255}
#define CT_COLOR_PINK            (ctColorRGBA8){255, 000, 255, 255}

typedef struct { 
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ctColorRGBA8;

inline ctColorRGBA8 ctColorRGBA8FromFloat4(float input[4]) {
    ctColorRGBA8 result;
    result.r = (uint8_t)(ctSaturatef(input[0]) * 255.0f);
    result.g = (uint8_t)(ctSaturatef(input[1]) * 255.0f);
    result.b = (uint8_t)(ctSaturatef(input[2]) * 255.0f);
    result.a = (uint8_t)(ctSaturatef(input[3]) * 255.0f);
    return result;
}

inline ctColorRGBA8 ctColorRGBA8FromVec3(const ctVec3 rgb, const float a) {
    ctColorRGBA8 result;
    result.r = (uint8_t)(ctSaturatef(rgb.x) * 255.0f);
    result.g = (uint8_t)(ctSaturatef(rgb.y) * 255.0f);
    result.b = (uint8_t)(ctSaturatef(rgb.z) * 255.0f);
    result.a = (uint8_t)(ctSaturatef(a) * 255.0f);
    return result;
}