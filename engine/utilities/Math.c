/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Math.h"

#include "codegen/engine/utilities/Math.c.gen.h"

bool ctFloatCompare(const float a, const float b, const float threshold) {
   return ctAbsf(a - b) < threshold;
}
 
bool ctFloatApproxEqual(const float a, const float b) {
   return ctFloatCompare(a, b, 0.0001f);
}

bool ctMultiFloatCompare(const uint32_t count,
                                const float* a,
                                const float* b,
                                const float threshold) {
   for (uint32_t i = 0; i < count; i++) {
      bool result = ctFloatCompare(a[i], b[i], threshold);
      if (!result) { return false; }
   }
   return true;
}

float ctLerpf(const float a, const float b, const float t) {
   return (1.0f - t) * a + t * b;
}

float ctSmoothStepf(const float a, const float b, const float t) {
   const float c = ctSaturatef((t - a) / (b - a));
   return c * c * (3.0f - 2.0f * c);
}

float ctPowf(const float a, const float b) {
   return powf(a, b);
}

float ctLogf(const float a) {
   return logf(a);
}

float ctSqrtf(const float a) {
   return sqrtf(a);
}

float ctInvSqrtf(const float a) {
   return 1.0f / sqrtf(a);
}

float ctAbsf(const float a) {
   return fabsf(a);
}

float ctExpf(const float power) {
   return expf(power);
}

float ctMaxf(const float a, const float b) {
   return a > b ? a : b;
}

float ctMinf(const float a, const float b) {
   return a < b ? a : b;
}

float ctClampf(const float a, const float min, const float max) {
   return ctMinf(ctMaxf(a, min), max);
}

float ctRemapf(
  const float v, const float in_min, const float in_max, float out_min, float out_max) {
   return out_min + (v - in_min) * (out_max - out_min) / (in_max - in_min);
}

float ctSaturatef(const float a) {
   return ctClampf(a, 0.0f, 1.0f);
}

float ctFloorf(const float a) {
   return floorf(a);
}

float ctCeilf(const float a) {
   return ceilf(a);
}

float ctRoundf(const float a) {
   return roundf(a);
}

float ctFracf(const float a) {
   return a - ctFloorf(a);
}

float ctRad2Degf(const float a) {
   return a * 57.29578f;
}

float ctDeg2Radf(const float a) {
   return a * 0.01745329f;
}

float ctSinf(const float a) {
    return fm_sinf(a);
}

float ctSinApproxf(const float a) {
    return fm_sinf_approx(a, 5);
}

float ctSinAccuratef(const float a) {
    return sinf(a);
}

float ctCosf(const float a) {
   return fm_cosf(a);
}

float ctCosAccuratef(const float a) {
    return cosf(a);
}

void ctSinCosf(const float a, float* sin, float* cos) {
    return fm_sincosf(a, sin, cos);
}

float ctTanf(const float a) {
   return tanf(a);
}

float ctArcSinf(const float a) {
   return asinf(a);
}

float ctArcCosf(const float a) {
   return acosf(a);
}

float ctArcTanf(const float a) {
   return atanf(a);
}

float ctArcTan2f(const float a, const float b) {
   return fm_atan2f(a, b);
}

float ctArcTan2Accuratef(const float a, const float b) {
    return atan2f(a, b);
}

bool ctIsPrime(const uint32_t x) {
   if (x < 2) { return false; /*actually undefined*/ }
   if (x < 4) { return true; }
   if ((x % 2) == 0) { return false; }
   for (uint32_t i = 3; i <= (uint32_t)ctFloorf(ctSqrtf((float)x)); i += 2) {
      if ((x % i) == 0) { return false; }
   }
   return true;
}

uint32_t ctNextPrime(uint32_t x) {
   while (!ctIsPrime(x)) {
      x++;
   }
   return x;
}