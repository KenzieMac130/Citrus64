/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Random.h

Random number generation for games
*/
#pragma once

#include "Common.h"
#include "Math3d.h"

#include "codegen/engine/utilities/Random.h.gen.h"

/*! @brief Holds a pcg random number generator state */
typedef struct {
   uint64_t state[2];
} ctRandomGenerator;

/*! @brief Initialize the random number generator with a seed */
CT_ENGINE_API ctRandomGenerator ctRandomGeneratorInitSeed(uint32_t seed);

/*! @brief Initialize the random number generator with a random seed */
CT_ENGINE_API ctRandomGenerator ctRandomGeneratorInit();

/*! @brief Get a random integer from 0 to UINT32_MAX */
CT_ENGINE_API uint32_t ctRandomGetUInt32(ctRandomGenerator* generator);

/*! @brief Get a random integer in a range */
CT_ENGINE_API int32_t ctRandomGetInt32Range(ctRandomGenerator* generator,
                                            int32_t min,
                                            int32_t max);

/*! @brief Get a random float in a range */
CT_ENGINE_API float ctRandomGetFloat(ctRandomGenerator* generator, float min, float max);
/*! @brief Get a random float from a -1.0f to 1.0f */
CT_ENGINE_API float ctRandomGetFloatSNorm(ctRandomGenerator* generator);
/*! @brief Get a random float from a 0.0f to 1.0f */
CT_ENGINE_API float ctRandomGetFloatUNorm(ctRandomGenerator* generator);

/*! @brief Get a random ctVec3 with unique components in their respective range */
CT_ENGINE_API ctVec3 ctRandomGetVec3Range(ctRandomGenerator* generator,
                                          const ctVec3 min,
                                          const ctVec3 max);
/*! @brief Get a random ctVec3 that has been normalized */
CT_ENGINE_API ctVec3 ctRandomGetVec3Norm(ctRandomGenerator* generator);

/*! @brief Get a random value in a gausian (normal) distribution

See: https://en.wikipedia.org/wiki/Normal_distribution
*/
CT_ENGINE_API float
ctRandomGetGaussian(ctRandomGenerator* generator, float mean, float standardDeviation);

/*! @brief Get a random xy pair in a gausian (normal) distribution

This ends up distributing points evenly in a 2D disk where standardDeviation is the radius
*/
CT_ENGINE_API void ctRandomGetGaussian2D(ctRandomGenerator* generator,
                                         float out[2],
                                         const float mean[2],
                                         float standardDeviation);

/*! @brief Get a random ctVec3 in a guasian distribution inside a 3D sphere */
CT_ENGINE_API ctVec3 ctRandomGetInSphere(ctRandomGenerator* generator, float radius);
/*! @brief Get a random ctVec3 in a guasian distribution on the surface of a 3D sphere */
CT_ENGINE_API ctVec3 ctRandomGetOnSphere(ctRandomGenerator* generator, float radius);

/*! @brief Get a random color (not guaranteed to be pleasing) */
CT_ENGINE_API ctColorRGBA8 ctRandomGetColor(ctRandomGenerator* generator, float alpha);