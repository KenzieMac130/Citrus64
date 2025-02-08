/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Math.h

Math library for extended floating point and integer math
*/
#pragma once

#include "Common.h"

/*! @brief Mathematical constant PI */
#define CT_PI   3.141592653589793238462643383279f

/*! @brief Float equality check

   Compares two floats for equality within 0.0001f difference
*/
inline bool ctFloatApproxEqual(const float a, const float b);

/*! @brief Float Compare
   Compares two floats for equality within a given threshold
*/
inline bool ctFloatCompare(const float a, const float b, const float threshold);

/*! @brief Compare multiple floats

   Similar to ctFloatCompare() but for multiple floats two a packed arrays
*/
inline bool ctMultiFloatCompare(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold);

/*! @brief Linear interpolation

   Mixes two numbers together based on a given factor
*/
inline float ctLerpf(const float a, const float b, const float factor);

/*! @brief Smoothstep interpolation

   See https://en.wikipedia.org/wiki/Smoothstep
*/
inline float ctSmoothStepf(const float a, const float b, const float factor);

/*! @brief Raises a value to an exponent */
inline float ctPowf(const float value, const float exponent);

/*! @brief Natural Logarithm */
inline float ctLogf(const float a);

/*! @brief Square Root */
inline float ctSqrtf(const float a);

/*! @brief Inverse Square Root */
inline float ctInvSqrtf(const float a);

/*! @brief Absolute value */
inline float ctAbsf(const float a);

/*! @brief Eulers number for a given power

   See https://en.wikipedia.org/wiki/E_(mathematical_constant)
*/
inline float ctExpf(const float power);

/*! @brief Take the maximum value between two numbers */
inline float ctMaxf(const float a, const float b);

/*! @brief Take the minimum value between two numbers */
inline float ctMinf(const float a, const float b);

/*! @brief Clamp number between a minimum and maximum range 
*/
inline float ctClampf(const float a, const float min, const float max);

/*! @brief Remap a number from a minimum and maximum range to a new minimum and maximum range 
*/
inline float ctRemapf(
  const float v, const float in_min, const float in_max, float out_min, float out_max);

/*! @brief Saturate clamps a value to a 0-1 range
*/
inline float ctSaturatef(const float a);

/*! @brief Round down a number to the last integer
*/
inline float ctFloorf(const float a);

/*! @brief Round up a number to the next integer
*/
inline float ctCeilf(const float a);

/*! @brief Round a number to the nearest integer
*/
inline float ctRoundf(const float a);

/*! @brief The remainder of a number after truncation   
*/
inline float ctFracf(const float a);

/*! @brief Radians to Degrees */
inline float ctRad2Degf(const float a);

/*! @brief Degrees to Radians */
inline float ctDeg2Radf(const float a);

/*! @brief Sine */
inline float ctSinf(const float a);

/*! @brief Approximate Sine Wave 

   Do not use for anything requiring precision
   Useful for pulsing animation effects
*/
inline float ctSinApproxf(const float a);

/*! @brief Accurate Sine 

   A more accurate version of ctSinf()
   Use if you hit an edge case requiring a higher accuracy
*/
inline float ctSinAccuratef(const float a);

/*! @brief Cosine */
inline float ctCosf(const float a);

/*! @brief Accurate Cosine 

   A more accurate version of ctCosf()
   Use if you hit an edge case requiring a higher accuracy
*/
inline float ctCosAccuratef(const float a);

/*! @brief Sign and cosine at once

   If you need to calculate both you can optimize by using this function   
*/
inline void ctSinCosf(const float a, float* sin, float* cos);

/*! @brief Tangent */
inline float ctTanf(const float a);

/*! @brief Arcsine */
inline float ctArcSinf(const float a);

/*! @brief Arccosine */
inline float ctArcCosf(const float a);

/*! @brief Arctangent */
inline float ctArcTanf(const float a);

/*! @brief ArcTan2 (atan2)

   See https://en.wikipedia.org/wiki/Atan2
*/
inline float ctArcTan2f(const float a, const float b);

/*! @brief Accurate Arctan2 (atan2)

   A more accurate version of ctArcTan2f()
   Use if you hit an edge case requiring a higher accuracy
*/
inline float ctArcTan2Accuratef(const float a, const float b);

/*! @brief Check if input is prime number */
inline bool ctIsPrime(const uint32_t x);

/*! @brief Find the next prime number after the input */
inline uint32_t ctNextPrime(uint32_t x);

/* ------------------ Implementations ------------------ */

inline bool ctFloatCompare(const float a, const float b, const float threshold) {
   return ctAbsf(a - b) < threshold;
}

inline bool ctFloatApproxEqual(const float a, const float b) {
   return ctFloatCompare(a, b, 0.0001f);
}

inline bool ctMultiFloatCompare(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold) {
   for (uint32_t i = 0; i < count; i++) {
      bool result = ctFloatCompare(a[i], b[i], threshold);
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

inline float ctInvSqrtf(const float a) {
   return 1.0f / ctSqrtf(a);
}

inline float ctAbsf(const float a) {
   return fabsf(a);
}

inline float ctExpf(const float power) {
   return expf(power);
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