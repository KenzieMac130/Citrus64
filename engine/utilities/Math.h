/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Math.h

Math library for extended floating point and integer math
*/
#pragma once

#include "Common.h"

#include "codegen/engine/utilities/Math.h.gen.h"

/*! @brief Mathematical constant PI */
#define CT_PI   3.141592653589793238462643383279f

/*! @brief Float equality check

   Compares two floats for equality within 0.0001f difference
*/
bool ctFloatApproxEqual(const float a, const float b);

/*! @brief Float Compare
   Compares two floats for equality within a given threshold
*/
bool ctFloatCompare(const float a, const float b, const float threshold);

/*! @brief Compare multiple floats

   Similar to ctFloatCompare() but for multiple floats two a packed arrays
*/
bool ctMultiFloatCompare(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold);

/*! @brief Linear interpolation

   Mixes two numbers together based on a given factor
*/
float ctLerpf(const float a, const float b, const float factor);

/*! @brief Smoothstep interpolation

   See https://en.wikipedia.org/wiki/Smoothstep
*/
float ctSmoothStepf(const float a, const float b, const float factor);

/*! @brief Raises a value to an exponent */
float ctPowf(const float value, const float exponent);

/*! @brief Natural Logarithm */
float ctLogf(const float a);

/*! @brief Square Root */
float ctSqrtf(const float a);

/*! @brief Inverse Square Root */
float ctInvSqrtf(const float a);

/*! @brief Absolute value */
float ctAbsf(const float a);

/*! @brief Eulers number for a given power

   See https://en.wikipedia.org/wiki/E_(mathematical_constant)
*/
float ctExpf(const float power);

/*! @brief Take the maximum value between two numbers */
float ctMaxf(const float a, const float b);

/*! @brief Take the minimum value between two numbers */
float ctMinf(const float a, const float b);

/*! @brief Clamp number between a minimum and maximum range 
*/
float ctClampf(const float a, const float min, const float max);

/*! @brief Remap a number from a minimum and maximum range to a new minimum and maximum range 
*/
float ctRemapf(
  const float v, const float in_min, const float in_max, float out_min, float out_max);

/*! @brief Saturate clamps a value to a 0-1 range
*/
float ctSaturatef(const float a);

/*! @brief Round down a number to the last integer
*/
float ctFloorf(const float a);

/*! @brief Round up a number to the next integer
*/
float ctCeilf(const float a);

/*! @brief Round a number to the nearest integer
*/
float ctRoundf(const float a);

/*! @brief The remainder of a number after truncation   
*/
float ctFracf(const float a);

/*! @brief Radians to Degrees */
float ctRad2Degf(const float a);

/*! @brief Degrees to Radians */
float ctDeg2Radf(const float a);

/*! @brief Sine */
float ctSinf(const float a);

/*! @brief Approximate Sine Wave 

   Do not use for anything requiring precision
   Useful for pulsing animation effects
*/
float ctSinApproxf(const float a);

/*! @brief Accurate Sine 

   A more accurate version of ctSinf()
   Use if you hit an edge case requiring a higher accuracy
*/
float ctSinAccuratef(const float a);

/*! @brief Cosine */
float ctCosf(const float a);

/*! @brief Accurate Cosine 

   A more accurate version of ctCosf()
   Use if you hit an edge case requiring a higher accuracy
*/
float ctCosAccuratef(const float a);

/*! @brief Sign and cosine at once

   If you need to calculate both you can optimize by using this function   
*/
void ctSinCosf(const float a, float* sin, float* cos);

/*! @brief Tangent */
float ctTanf(const float a);

/*! @brief Arcsine */
float ctArcSinf(const float a);

/*! @brief Arccosine */
float ctArcCosf(const float a);

/*! @brief Arctangent */
float ctArcTanf(const float a);

/*! @brief ArcTan2 (atan2)

   See https://en.wikipedia.org/wiki/Atan2
*/
float ctArcTan2f(const float a, const float b);

/*! @brief Accurate Arctan2 (atan2)

   A more accurate version of ctArcTan2f()
   Use if you hit an edge case requiring a higher accuracy
*/
float ctArcTan2Accuratef(const float a, const float b);

/*! @brief Check if input is prime number */
bool ctIsPrime(const uint32_t x);

/*! @brief Find the next prime number after the input */
uint32_t ctNextPrime(uint32_t x);