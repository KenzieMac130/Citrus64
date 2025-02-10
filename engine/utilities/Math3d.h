/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Math3d.h

Math functions for working with 3D space
*/
#pragma once

#include "Common.h"

#include "codegen/engine/utilities/Math3d.h.gen.h"

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
#define CT_VEC3_UP                                                                       \
   (ctVec3) {                                                                            \
      CT_UP                                                                              \
   }
#define CT_VEC3_DOWN                                                                     \
   (ctVec3) {                                                                            \
      CT_DOWN                                                                            \
   }
#define CT_VEC3_FORWARD                                                                  \
   (ctVec3) {                                                                            \
      CT_FORWARD                                                                         \
   }
#define CT_VEC3_BACK                                                                     \
   (ctVec3) {                                                                            \
      CT_BACK                                                                            \
   }
#define CT_VEC3_RIGHT                                                                    \
   (ctVec3) {                                                                            \
      CT_RIGHT                                                                           \
   }
#define CT_VEC3_LEFT                                                                     \
   (ctVec3) {                                                                            \
      CT_LEFT                                                                            \
   }

/*! @brief 3D Vector */
typedef struct {
   float x;
   float y;
   float z;
} __attribute__((aligned(16))) ctVec3;

/*! @brief Construct a (0, 0, 0) vector */
ctVec3 ctVec3Zero();

/*! @brief Construct a vector from XYZ */
ctVec3 ctVec3Make(float x, float y, float z);

/*! @brief Construct a (1, 1, 1) vector */
ctVec3 ctVec3Identity();

/*! @brief Construct a vector from a float triplet pointer */
ctVec3 ctVec3FromFloat3(const float data[3]);

/*! @brief Construct a vector filled with a single value */
ctVec3 ctVec3FromFloat(float value);

/*! @brief Is this vector approximately equal to another */
bool ctVec3ApproxEqual(const ctVec3 a, const ctVec3 b);

/*! @brief Add another vector to this vector */
void ctVec3Add(ctVec3* a, const ctVec3 b);

/*! @brief Subtract another vector from this vector */
void ctVec3Sub(ctVec3* a, const ctVec3 b);

/*! @brief Invert this vector's component's signs */
void ctVec3Negate(ctVec3* v);

/*! @brief Multiply this vector by another vector */
void ctVec3Mult(ctVec3* a, const ctVec3 b);

/*! @brief Multiply this vector by a float */
void ctVec3Scale(ctVec3* a, const float b);

/*! @brief Divide this vector by another vector */
void ctVec3Divide(ctVec3* a, const ctVec3 b);

/*! @brief Divide this vector by a float */
void ctVec3DivideFloat(ctVec3* a, const float b);

/*! @brief Get a dot product between two vectors */
float ctVec3Dot(const ctVec3 a, const ctVec3 b);

/*! @brief Get the distance between two vectors */
float ctVec3Distance(const ctVec3 a, const ctVec3 b);

/*! @brief Get the length (magnitude) of a vector */
float ctVec3Length(const ctVec3 v);

/*! @brief Make this vector's components positive */
void ctVec3Abs(ctVec3* v);

/*! @brief Make this vector a unit length vector */
void ctVec3Normalize(ctVec3* v);

/*! @brief Clamp this vector from 0-1 */
void ctVec3Saturate(ctVec3* v);

/*! @brief Fill this vector with the cross product between two vectors */
void ctVec3Cross(ctVec3* out, const ctVec3 a, const ctVec3 b);

/*! @brief Fill this vector with the lerp result between two vectors */
void ctVec3Lerp(ctVec3* out, const ctVec3 a, const ctVec3 b, const float t);

/* ------- Quaternion -------*/

/*! @brief Represents a 3D rotation using imaginary numbers */
typedef struct {
   float x;
   float y;
   float z;
   float w;
} __attribute__((aligned(16))) ctQuat;

/*! @brief Construct a quaternion that has no affect when rotated */
ctQuat ctQuatIdentity();

/*! @brief Construct a quaternion from a float pointer to 4 values */
ctQuat ctQuatFromFloat4(const float v[4]);

/*! @brief Construct a quaternion that represents a rotation around an axis */
ctQuat ctQuatFromAxisAngle(const ctVec3 axis, float angle);

/*! @brief Construct a quaternion from a euler rotation */
ctQuat ctQuatFromEuler(const ctVec3 euler);

/*! @brief Rotate this quaternion by another quaternion */
void ctQuatRotate(ctQuat* a, const ctQuat b);

/*! @brief Invert the rotation of this quaternion */
void ctQuatInvert(ctQuat* v);

/*! @brief Fix any issues in this quaternion */
void ctQuatNormalize(ctQuat* v);

/*! @brief Rotate a vector by a given quaternion */
void ctQuatRotateVec3(ctVec3* vector, const ctQuat q);

/*! @brief Get the forward vector of this quaternion */
ctVec3 ctQuatGetForward(const ctQuat q);

/*! @brief Get the back vector of this quaternion */
ctVec3 ctQuatGetBack(const ctQuat q);

/*! @brief Get the up vector of this quaternion */
ctVec3 ctQuatGetUp(const ctQuat q);

/*! @brief Get the down vector of this quaternion */
ctVec3 ctQuatGetDown(const ctQuat q);

/*! @brief Get the right vector of this quaternion */
ctVec3 ctQuatGetRight(const ctQuat q);

/*! @brief Get the left vector of this quaternion */
ctVec3 ctQuatGetLeft(const ctQuat q);

/*! @brief Construct a quaternion that looks at a target from a given orientation */
ctQuat ctQuatLookAt(const ctVec3 direction, const ctVec3 forward, const ctVec3 up);

/*! @brief Construct a quaternion that takes part of the shortest path on a sphere between
 * two rotations */
void ctQuatSlerp(ctQuat* dest, const ctQuat a, const ctQuat b, float t);

/* ------- Color -------*/

/*! @brief Represents one or more color channels */
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

#define CT_COLOR_BLACK           (ctColorRGBA8) {000, 000, 000, 255}
#define CT_COLOR_GREY            (ctColorRGBA8) {127, 127, 127, 255}
#define CT_COLOR_WHITE           (ctColorRGBA8) {255, 255, 255, 255}
#define CT_COLOR_INVISIBLE_BLACK (ctColorRGBA8) {000, 000, 000, 000}
#define CT_COLOR_INVISIBLE_GREY  (ctColorRGBA8) {127, 127, 127, 000}
#define CT_COLOR_INVISIBLE_WHITE (ctColorRGBA8) {255, 255, 255, 000}
#define CT_COLOR_RED             (ctColorRGBA8) {255, 000, 000, 255}
#define CT_COLOR_GREEN           (ctColorRGBA8) {000, 255, 000, 255}
#define CT_COLOR_BLUE            (ctColorRGBA8) {000, 000, 255, 255}
#define CT_COLOR_YELLOW          (ctColorRGBA8) {255, 255, 000, 255}
#define CT_COLOR_ORANGE          (ctColorRGBA8) {255, 127, 000, 255}
#define CT_COLOR_PURPLE          (ctColorRGBA8) {127, 000, 255, 255}
#define CT_COLOR_PINK            (ctColorRGBA8) {255, 000, 255, 255}

/*! @brief Represents a color using 8 bit unsigned normalized values */
typedef struct {
   uint8_t r;
   uint8_t g;
   uint8_t b;
   uint8_t a;
} ctColorRGBA8;

/*! @brief Convert a pointer to four floats into a color */
ctColorRGBA8 ctColorRGBA8FromFloat4(float input[4]);

/*! @brief Convert vector representing rgb into a color with a given alpha */
ctColorRGBA8 ctColorRGBA8FromVec3(const ctVec3 rgb, const float a);