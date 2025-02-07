/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "Common.h"

#define CT_PI   3.141592653589793238462643383279f
#define CT_PI_D 3.141592653589793238462643383279

/* Float Compare */
inline bool ctFloatEqual(const float a, const float b, const float threshold);

/* Compare multiple floats */
inline bool ctMultiFloatEqual(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold);

/* Lerp */
inline float ctLerpf(const float a, const float b, const float factor);

/* Smoothstep */
inline float ctSmoothStepf(const float a, const float b, const float factor);

/* Power */
inline float ctPowf(const float a, const float b);

/* Log */
inline float ctLogf(const float a);

/* Sqrt */
inline float ctSqrtf(const float a);

/* Abs */
inline float ctAbsf(const float a);

/* Exp */
inline float ctExpf(const float a);

/* Max */
inline float ctMaxf(const float a, const float b);

/* Min */
inline float ctMinf(const float a, const float b);

/* Clamp */
inline float ctClampf(const float a, const float min, const float max);

/* Remapping */
inline float ctRemapf(
  const float v, const float in_min, const float in_max, float out_min, float out_max);

/* Saturate */
inline float ctSaturatef(const float a);

/* Floor */
inline float ctFloorf(const float a);

/* Ceil */
inline float ctCeilf(const float a);

/* Round */
inline float ctRoundf(const float a);

/* Frac */
inline float ctFracf(const float a);

/* RadiansToDegrees */
inline float ctRad2Degf(const float a);

/* DegreesToRadians */
inline float ctDeg2Radf(const float a);

/* Sine */
inline float ctSinf(const float a);
inline float ctSinApproxf(const float a);
inline float ctSinAccuratef(const float a);

/* Cosine */
inline float ctCosf(const float a);
inline float ctCosAccuratef(const float a);

/* Sign and cosine at once */
inline void ctSinCosf(const float a, float* sin, float* cos);

/* Tan */
inline float ctTanf(const float a);

/* ArcSin */
inline float ctArcSinf(const float a);

/* ArcCos */
inline float ctArcCosf(const float a);

/* ArcTan */
inline float ctArcTanf(const float a);

/* ArcTan2 */
inline float ctArcTan2f(const float a, const float b);
inline float ctArcTan2Accuratef(const float a, const float b);

/* Prime number */
inline bool ctIsPrime(const uint32_t x);
inline uint32_t ctNextPrime(uint32_t x);

/* ------------------ Implementations ------------------ */

inline bool ctFloatEqual(const float a, const float b, const float threshold) {
   return ctAbsf(a - b) < threshold;
}

inline bool ctMultiFloatEqual(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold) {
   for (uint32_t i = 0; i < count; i++) {
      bool result = ctFloatEqual(a[i], b[i], threshold);
      if (!result) { return false; }
   }
   return true;
}

inline float ctLerpf(const float a, const float b, const float t) {
   return (1.0f - t) * a + t * b;
}

inline float ctSmoothStepf(const float a, const float b, const float t) {
   const float c = ctSaturatef((t - a) / (b - a));
   return c * c * (3.0f - 2.0f * c);
}

inline float ctPowf(const float a, const float b) {
   return powf(a, b);
}

inline float ctLogf(const float a) {
   return logf(a);
}

inline float ctSqrtf(const float a) {
   return sqrtf(a);
}

inline float ctAbsf(const float a) {
   return fabsf(a);
}

inline float ctExpf(const float a) {
   return expf(a);
}

inline float ctMaxf(const float a, const float b) {
   return a > b ? a : b;
}

inline float ctMinf(const float a, const float b) {
   return a < b ? a : b;
}

inline float ctClampf(const float a, const float min, const float max) {
   return ctMinf(ctMaxf(a, min), max);
}

inline float ctRemapf(
  const float v, const float in_min, const float in_max, float out_min, float out_max) {
   return out_min + (v - in_min) * (out_max - out_min) / (in_max - in_min);
}

inline float ctSaturatef(const float a) {
   return ctClampf(a, 0.0f, 1.0f);
}

inline float ctFloorf(const float a) {
   return floorf(a);
}

inline float ctCeilf(const float a) {
   return ceilf(a);
}

inline float ctRoundf(const float a) {
   return roundf(a);
}

inline float ctFracf(const float a) {
   return a - ctFloorf(a);
}

inline float ctRad2Degf(const float a) {
   return a * 57.29578f;
}

inline float ctDeg2Radf(const float a) {
   return a * 0.01745329f;
}

inline float ctSinf(const float a) {
    return fm_sinf(a);
}

inline float ctSinApproxf(const float a) {
    return fm_sinf_approx(a, 5);
}

inline float ctSinAccuratef(const float a) {
    return sinf(a);
}

inline float ctCosf(const float a) {
   return fm_cosf(a);
}

inline float ctCosAccuratef(const float a) {
    return cosf(a);
}

inline void ctSinCosf(const float a, float* sin, float* cos) {
    return fm_sincosf(a, sin, cos);
}

inline float ctTanf(const float a) {
   return tanf(a);
}

inline float ctArcSinf(const float a) {
   return asinf(a);
}

inline float ctArcCosf(const float a) {
   return acosf(a);
}

inline float ctArcTanf(const float a) {
   return atanf(a);
}

inline float ctArcTan2f(const float a, const float b) {
   return fm_atan2f(a, b);
}

inline float ctArcTan2Accuratef(const float a, const float b) {
    return atan2f(a, b);
}

inline bool ctIsPrime(const uint32_t x) {
   if (x < 2) { return false; /*actually undefined*/ }
   if (x < 4) { return true; }
   if ((x % 2) == 0) { return false; }
   for (uint32_t i = 3; i <= (uint32_t)ctFloorf(ctSqrtf((float)x)); i += 2) {
      if ((x % i) == 0) { return false; }
   }
   return true;
}

inline uint32_t ctNextPrime(uint32_t x) {
   while (!ctIsPrime(x)) {
      x++;
   }
   return x;
}