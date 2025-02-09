/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Math3d.h"

/* ------- Vector3 -------*/

ctVec3 ctVec3Zero() {
    return (ctVec3){0.0f, 0.0f, 0.0f};
}

ctVec3 ctVec3Make(float x, float y, float z) {
    return (ctVec3){x, y, z};
}

ctVec3 ctVec3Identity() {
    return (ctVec3){1.0f, 1.0f, 1.0f};
}

ctVec3 ctVec3FromFloat3(const float data[3]) {
    ctAssert(data);
    return (ctVec3){data[0], data[1], data[2]};
}

ctVec3 ctVec3FromFloat(float value) {
    return (ctVec3){value, value, value};
}

bool ctVec3ApproxEqual(const ctVec3 a, const ctVec3 b) {
    return ctMultiFloatCompare(3, (float*)&a, (float*)&b, 0.0001f);
}

void ctVec3Add(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

void ctVec3Sub(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

void ctVec3Negate(ctVec3* v) {
    ctAssert(v);
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void ctVec3Mult(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

void ctVec3Scale(ctVec3* a, const float b) {
    ctAssert(a);
    a->x *= b;
    a->y *= b;
    a->z *= b;
}

void ctVec3Divide(ctVec3* a, const ctVec3 b) {
    ctAssert(a);
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
}

void ctVec3DivideFloat(ctVec3* a, const float b) {
    ctAssert(a);
    a->x /= b;
    a->y /= b;
    a->z /= b;
}

float ctVec3Dot(const ctVec3 a, const ctVec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float ctVec3Distance(const ctVec3 a, const ctVec3 b) {
    return ctSqrtf(ctPowf(a.x - b.x, 2.0f) + ctPowf(a.y - b.y, 2.0f) +
                   ctPowf(a.z - b.z, 2.0f));
}

float ctVec3Length(const ctVec3 v) {
    return ctSqrtf(ctVec3Dot(v, v));
}

void ctVec3Abs(ctVec3* v) {
    ctAssert(v);
    v->x = ctAbsf(v->x);
    v->y = ctAbsf(v->y);
    v->z = ctAbsf(v->z);
}

void ctVec3Normalize(ctVec3* v) {
    ctAssert(v);
    ctVec3DivideFloat(v, ctVec3Length(*v));
}

void ctVec3Saturate(ctVec3* v) {
    ctAssert(v);
    v->x = ctSaturatef(v->x);
    v->y = ctSaturatef(v->y);
    v->z = ctSaturatef(v->z);
}

void ctVec3Cross(ctVec3* out, const ctVec3 a, const ctVec3 b) {
    ctAssert(out);
    out->x = a.y * b.z - b.y * a.z;
    out->y = a.z * b.x - b.z * a.x;
    out->z = a.x * b.y - b.x * a.y;
}

void ctVec3Lerp(ctVec3* out, const ctVec3 a, const ctVec3 b, const float t) {
    ctAssert(out);
    out->x = ctLerpf(a.x, b.x, t);
    out->y = ctLerpf(a.y, b.y, t);
    out->z = ctLerpf(a.z, b.z, t);
}

/* ------- Quaternion -------*/

ctQuat ctQuatIdentity() {
    return (ctQuat){0.0f, 0.0f, 0.0f, 1.0f};
}
ctQuat ctQuatFromFloat4(const float v[4]) {
    return (ctQuat){v[0], v[1], v[2], v[3]};
}

ctQuat ctQuatFromAxisAngle(const ctVec3 axis, float angle) {
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

ctQuat ctQuatFromEuler(const ctVec3 euler) {
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

void ctQuatRotate(ctQuat* a, const ctQuat b) {
    ctQuat result;
    result.x = a->w * b.x + a->x * b.w + a->y * b.z - a->z * b.y;
    result.y = a->w * b.y - a->x * b.z + a->y * b.w + a->z * b.x;
    result.z = a->w * b.z + a->x * b.y - a->y * b.x + a->z * b.w;
    result.w = a->w * b.w - a->x * b.x - a->y * b.y - a->z - b.z;
    *a = result;
}

void ctQuatInvert(ctQuat* v) {
    /* todo */
}

void ctQuatNormalize(ctQuat* v) {
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

void ctQuatRotateVec3(ctVec3* vector, const ctQuat q) {
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

ctVec3 ctQuatGetForward(const ctQuat q) {
    ctVec3 axis = CT_VEC3_FORWARD;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctVec3 ctQuatGetBack(const ctQuat q) {
    ctVec3 axis = CT_VEC3_BACK;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctVec3 ctQuatGetUp(const ctQuat q) {
    ctVec3 axis = CT_VEC3_UP;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctVec3 ctQuatGetDown(const ctQuat q) {
    ctVec3 axis = CT_VEC3_DOWN;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctVec3 ctQuatGetRight(const ctQuat q) {
    ctVec3 axis = CT_VEC3_RIGHT;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctVec3 ctQuatGetLeft(const ctQuat q) {
    ctVec3 axis = CT_VEC3_LEFT;
    ctQuatRotateVec3(&axis, q);
    return axis;
}

ctQuat ctQuatLookAt(const ctVec3 direction, const ctVec3 forward, const ctVec3 up) {
 ctQuat result = ctQuatIdentity();
// glm_quat_for((float*)dir.data, (float*)fwd.data, (float*)up.data, (float*)result.data);
 return result;
}

void ctQuatSlerp(ctQuat* dest, const ctQuat a, const ctQuat b, float t) {
    //float cosTheta, sinTheta, angle;
    /* https://github.com/recp/cglm/blob/master/include/cglm/quat.h#L321 */
}

/* ------- Color -------*/

ctColorRGBA8 ctColorRGBA8FromFloat4(float input[4]) {
    ctColorRGBA8 result;
    result.r = (uint8_t)(ctSaturatef(input[0]) * 255.0f);
    result.g = (uint8_t)(ctSaturatef(input[1]) * 255.0f);
    result.b = (uint8_t)(ctSaturatef(input[2]) * 255.0f);
    result.a = (uint8_t)(ctSaturatef(input[3]) * 255.0f);
    return result;
}

ctColorRGBA8 ctColorRGBA8FromVec3(const ctVec3 rgb, const float a) {
    ctColorRGBA8 result;
    result.r = (uint8_t)(ctSaturatef(rgb.x) * 255.0f);
    result.g = (uint8_t)(ctSaturatef(rgb.y) * 255.0f);
    result.b = (uint8_t)(ctSaturatef(rgb.z) * 255.0f);
    result.a = (uint8_t)(ctSaturatef(a) * 255.0f);
    return result;
}