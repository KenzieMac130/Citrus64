/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "Random.h"
#include "Math.h"

#define RND_IMPLEMENTATION
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#include "thirdparty/mattias/rnd.h"

#include "codegen/engine/utilities/Random.c.gen.h"

ctRandomGenerator ctRandomGeneratorInitSeed(uint32_t seed) {
   ctRandomGenerator result;
   rnd_pcg_seed(&result.state, seed);
   return result;
}

ctRandomGenerator ctRandomGeneratorInit() {
   return ctRandomGeneratorInitSeed((uint32_t)rand());
}

uint32_t ctRandomGetUInt32(ctRandomGenerator* generator) {
   return rnd_pcg_next(&generator->state);
}

int32_t ctRandomGetInt32Range(ctRandomGenerator* generator, int32_t min, int32_t max) {
   return rnd_pcg_range(&generator->state, min, max);
}

float ctRandomGetFloatUNorm(ctRandomGenerator* generator) {
   return rnd_pcg_nextf(&generator->state);
}

float ctRandomGetFloatSNorm(ctRandomGenerator* generator) {
   return ctRandomGetFloatUNorm(generator) * 2.0f - 1.0f;
}

float ctRandomGetFloat(ctRandomGenerator* generator, float min, float max) {
   return ctRemapf(ctRandomGetFloatUNorm(generator), 0.0f, 1.0f, min, max);
}

ctVec3 ctRandomGetVec3Range(ctRandomGenerator* gen, const ctVec3 min, const ctVec3 max) {
   return ctVec3Make(ctRandomGetFloat(gen, min.x, max.x),
                     ctRandomGetFloat(gen, min.y, max.y),
                     ctRandomGetFloat(gen, min.z, max.z));
}

ctVec3 ctRandomGetVec3Norm(ctRandomGenerator* gen) {
   ctVec3 result = ctVec3Make(
     ctRandomGetFloatUNorm(gen), ctRandomGetFloatUNorm(gen), ctRandomGetFloatUNorm(gen));
   ctVec3Normalize(&result);
   return result;
}

float ctRandomGetGaussian(ctRandomGenerator* gen, float mean, float standardDeviation) {
   const float theta = 2.0f * CT_PI * ctRandomGetFloatUNorm(gen);
   const float rho =
     ctSqrtf(-2.0f * ctLogf(1.0f - (ctRandomGetFloatUNorm(gen) + FLT_EPSILON)));
   const float scale = standardDeviation * rho;
   return mean + scale * ctCosf(theta);
}

void ctRandomGetGaussian2D(ctRandomGenerator* gen,
                           float out[2],
                           const float mean[2],
                           float standardDeviation) {
   const float theta = 2.0f * CT_PI * ctRandomGetFloatUNorm(gen);
   const float rho =
     ctSqrtf(-2.0f * ctLogf(1.0f - (ctRandomGetFloatUNorm(gen) + FLT_EPSILON)));
   const float scale = standardDeviation * rho;
   float ctheta, stheta;
   ctSinCosf(theta, &stheta, &ctheta);
   out[0] = mean[0] * scale * ctheta;
   out[1] = mean[1] * scale * stheta;
}

ctVec3 ctRandomGetInSphere(ctRandomGenerator* gen, float radius) {
   ctVec3 result;
   const float dz[] = {0.0f, 0.0f};
   ctRandomGetGaussian2D(gen, (float*)&result, dz, 1.0f / CT_PI * radius);
   result.z = ctRandomGetGaussian(gen, 0.0f, 1.0f / CT_PI * radius);
   return result;
}

ctVec3 ctRandomGetOnSphere(ctRandomGenerator* generator, float radius) {
   ctVec3 result = ctRandomGetInSphere(generator, 1.0f);
   ctVec3Normalize(&result);
   ctVec3Scale(&result, radius * 0.5f);
   return result;
}

ctColorRGBA8 ctRandomGetColor(ctRandomGenerator* generator, float alpha) {
   ctVec3 rgb =
     ctRandomGetVec3Range(generator, ctVec3FromFloat(0.0f), ctVec3FromFloat(1.0f));
   return ctColorRGBA8FromVec3(rgb, alpha);
}

void _ctRandomHardwareInit() {
   srand(getentropy32());
   register_VI_handler((void (*)(void))rand);
}

#pragma GCC diagnostic pop