/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file ECSCore.h

The foundations of the entity component system
*/

#include "engine/utilities/Utilities.h"

#include "codegen/engine/scene/ECSCore.h.gen.h"

typedef uint8_t ctEntity;

#define CT_ENTITY_IDX(_ENT) _ENT
#define CT_ENTITY_INVALID   0

/* --------------------- Flags --------------------- */

typedef struct {
   uint8_t bytes[255];
} ctECSFlags;

#define CT_DECLARE_ECS_FLAGS(_NAME)                                                      \
   void ctECSFlagSet##_NAME(ctEntity entity);                                            \
   void ctECSFlagUnset##_NAME(ctEntity entity);                                          \
   bool ctECSFlagGet##_NAME(ctEntity entity);                                            \
   /*ctECSFlags* ctECSFlags##_NAME();*/                                                  \
   uint32_t ctECSItCount##_NAME();                                                       \
   bool ctECSItGetState##_NAME(uint32_t idx);                                            \
   ctEntity ctECSItGetEntity##_NAME(uint32_t idx);

#define CT_DEFINE_ECS_FLAGS(_NAME)                                                       \
   ctECSFlags gEntityFlag##_NAME;                                                        \
                                                                                         \
   void ctECSSetFlag##_NAME(ctEntity entity) {                                           \
      gEntityFlag##_NAME.bytes[CT_ENTITY_IDX(entity)] = true;                            \
   }                                                                                     \
   void ctECSUnsetFlag##_NAME(ctEntity entity) {                                         \
      gEntityFlag##_NAME.bytes[CT_ENTITY_IDX(entity)] = false;                           \
   }                                                                                     \
   bool ctECSGetFlag##_NAME(ctEntity entity) {                                           \
      return gEntityFlag##_NAME.bytes[CT_ENTITY_IDX(entity)];                            \
   }                                                                                     \
   /*ctECSFlags* ctECSFlags##_NAME() {                                                   \
      return &gEntityFlag##_NAME;                                                        \
   }*/                                                                                   \
   uint32_t ctECSItCount##_NAME() {                                                      \
      return 254;                                                                        \
   }                                                                                     \
   bool ctECSItGetState##_NAME(uint32_t idx) {                                           \
      return ctECSGetFlag##_NAME(idx);                                                   \
   }                                                                                     \
   ctEntity ctECSItGetEntity##_NAME(uint32_t idx) {                                      \
      return idx;                                                                        \
   }

/* --------------------- Flag Cache --------------------- */

// typedef struct {
//    uint8_t bits[32];
// } ctECSFlagCache;

// inline void ctECSFlagCacheSetBit(ctECSFlagCache* cache, int idx, int cond) {
//    const int byte = idx / 8;
//    const int bit = idx % 8;
//    cache->bits[byte] |= cond << bit;
// }

// inline void ctECSFlagCacheToggleBit(ctECSFlagCache* cache, int idx, int value) {
//    const int byte = idx / 8;
//    const int bit = idx % 8;
//    cache->bits[byte] |= ~(1 << bit) | (value << bit);
// }

// inline void ctECSFlagCacheUnsetBit(ctECSFlagCache* cache, int idx, int cond) {
//    const int byte = idx / 8;
//    const int bit = idx % 8;
//    cache->bits[byte] &= ~(cond << bit);
// }

// inline void ctECSFlagCacheAndBit(ctECSFlagCache* cache, int idx, int cond) {
//    const int byte = idx / 8;
//    const int bit = idx % 8;
//    cache->bits[byte] &= (cond << bit);
// }

// inline bool ctECSFlagCacheGetBit(const ctECSFlagCache* cache, int idx) {
//    const int byte = idx / 8;
//    const int bit = idx % 8;
//    return (bool)((cache->bits[byte] & (1 << bit)) >> bit);
// }

// inline void ctECSFlagCacheClear(ctECSFlagCache* cache) {
//    memset(cache->bits, 0, sizeof(cache->bits));
// }

// inline void ctECSFlagCacheSet(ctECSFlagCache* cache, const ctECSFlags* flags) {
//    for (int i = 0; i < 254; i++) {
//       ctECSFlagCacheSetBit(cache, flags->bytes[i], 1);
//    }
// }

// inline void ctECSFlagCacheAdd(ctECSFlagCache* cache, const ctECSFlags* flags) {
//    for (int i = 0; i < 254; i++) {
//       if (flags->bytes[i]) { ctECSFlagCacheSetBit(cache, flags->bytes[i], 1); }
//    }
// }

// inline void ctECSFlagCacheSubtract(ctECSFlagCache* cache, const ctECSFlags* flags) {
//    for (int i = 0; i < 254; i++) {
//       ctECSFlagCacheUnsetBit(cache, flags->bytes[i], 1);
//    }
// }

// inline bool ctECSFlagCacheIsEnabled(const ctECSFlagCache* cache, ctEntity entity) {
//    return ctECSFlagCacheGetBit(cache, CT_ENTITY_IDX(entity));
// }

/* --------------------- Component --------------------- */

#define CT_ECS_DESTRUCTOR_NONE(_PTR)

#define CT_COMPONENT_INVALID 255
#define CT_COMPONENT_MAX     254

#define CT_DECLARE_COMPONENT(_NAME, _TYPE)                                               \
   void ctECSInitialize##_NAME();                                                        \
                                                                                         \
   _TYPE* ctECSGet##_NAME(ctEntity entity);                                              \
   _TYPE* ctECSAdd##_NAME(ctEntity entity);                                              \
   void ctECSRemove##_NAME(ctEntity entity);                                             \
                                                                                         \
   uint32_t ctECSItCount##_NAME();                                                       \
   _TYPE* ctECSItGetComponent##_NAME(uint32_t idx);                                      \
   ctEntity ctECSItGetEntity##_NAME(uint32_t idx);                                       \
                                                                                         \
   /*ctECSFlagCache* ctECSFlagCache##_NAME();                                            \
   void ctECSFlagCacheSetHas##_NAME(ctECSFlagCache* cache);                              \
   void ctECSFlagCacheAddHas##_NAME(ctECSFlagCache* cache);                              \
   void ctECSFlagCacheSubtractHas##_NAME(ctECSFlagCache* cache);                         \
   void ctECSFlagCacheAndHas##_NAME(ctECSFlagCache* cache);*/

#define CT_DEFINE_COMPONENT(_NAME, _TYPE, _MAX, _DESTRUCTOR)                               \
   ctStaticAssert(_MAX <= CT_COMPONENT_MAX);                                               \
   struct {                                                                                \
      /*ctECSFlagCache flagCache;*/                                                        \
      uint8_t componentCount;                                                              \
      uint8_t entityToComponent[255];                                                      \
      ctEntity componentToEntity[255];                                                     \
      uint8_t _pad0;                                                                       \
      _TYPE components[_MAX];                                                              \
   } gComponentFactory##_NAME;                                                             \
                                                                                           \
   void ctECSInitialize##_NAME() {                                                         \
      memset(&gComponentFactory##_NAME, 0, sizeof(gComponentFactory##_NAME));              \
      for (uint32_t i = 0; i < 255; i++) {                                                 \
         gComponentFactory##_NAME.entityToComponent[i] = CT_COMPONENT_INVALID;             \
      }                                                                                    \
   }                                                                                       \
                                                                                           \
   _TYPE* ctECSGet##_NAME(ctEntity entity) {                                               \
      const uint32_t entidx = CT_ENTITY_IDX(entity);                                       \
      const uint8_t idx = gComponentFactory##_NAME.entityToComponent[entidx];              \
      if (idx == CT_COMPONENT_INVALID) { return NULL; }                                    \
      return &gComponentFactory##_NAME.components[idx];                                    \
   }                                                                                       \
                                                                                           \
   _TYPE* ctECSAdd##_NAME(ctEntity entity) {                                               \
      if (gComponentFactory##_NAME.componentCount >= _MAX) { return NULL; }                \
      const uint32_t entidx = CT_ENTITY_IDX(entity);                                       \
      const uint8_t idx = gComponentFactory##_NAME.componentCount;                         \
      gComponentFactory##_NAME.entityToComponent[entidx] = idx;                            \
      gComponentFactory##_NAME.componentToEntity[idx] = entity;                            \
      gComponentFactory##_NAME.componentCount++;                                           \
      return &gComponentFactory##_NAME.components[idx];                                    \
   }                                                                                       \
                                                                                           \
   void ctECSRemove##_NAME(ctEntity entity) {                                              \
      const uint32_t entidx = CT_ENTITY_IDX(entity);                                       \
      const uint8_t idx = gComponentFactory##_NAME.entityToComponent[entidx];              \
      if (idx == CT_COMPONENT_INVALID) { return; }                                         \
      _DESTRUCTOR(&gComponentFactory##_NAME.components[idx]);                              \
      /* compact componentToEntity and components */                                       \
      for (uint32_t i = idx; i < gComponentFactory##_NAME.componentCount - 1; i++) {       \
         gComponentFactory##_NAME.components[i] =                                          \
           gComponentFactory##_NAME.components[i + 1];                                     \
         gComponentFactory##_NAME.componentToEntity[i] =                                   \
           gComponentFactory##_NAME.componentToEntity[i + 1];                              \
      }                                                                                    \
      /* update entityToComponent */                                                       \
      gComponentFactory##_NAME.entityToComponent[entidx] = CT_COMPONENT_INVALID;           \
      for (uint32_t i = 0; i < 255; i++) {                                                 \
         if (gComponentFactory##_NAME.entityToComponent[i] != CT_COMPONENT_INVALID &&      \
             gComponentFactory##_NAME.entityToComponent[i] >= idx) {                       \
            gComponentFactory##_NAME.entityToComponent[i]--;                               \
         }                                                                                 \
      }                                                                                    \
      gComponentFactory##_NAME.componentCount--;                                           \
   }                                                                                       \
                                                                                           \
   uint32_t ctECSItCount##_NAME() {                                                        \
      return (uint32_t)gComponentFactory##_NAME.componentCount;                            \
   }                                                                                       \
                                                                                           \
   _TYPE* ctECSItGetComponent##_NAME(uint32_t idx) {                                       \
      ctAssert(idx < gComponentFactory##_NAME.componentCount);                             \
      return &gComponentFactory##_NAME.components[idx];                                    \
   }                                                                                       \
                                                                                           \
   ctEntity ctECSItGetEntity##_NAME(uint32_t idx) {                                        \
      ctAssert(idx < gComponentFactory##_NAME.componentCount);                             \
      return gComponentFactory##_NAME.componentToEntity[idx];                              \
   }                                                                                       \
   /*                                                                                      \
   ctECSFlagCache* ctECSFlagCache##_NAME() {                                               \
      return &gComponentFactory##_NAME.flagCache;                                          \
   }                                                                                       \
                                                                                         \ \
   void ctECSFlagCacheSetHas##_NAME(ctECSFlagCache* cache) {                               \
      for (int i = 0; i < 255; i++) {                                                      \
         ctECSFlagCacheToggleBit(cache,                                                    \
                                 i,                                                        \
                                 gComponentFactory##_NAME.entityToComponent[i] !=          \
                                   CT_COMPONENT_INVALID);                                  \
      }                                                                                    \
   }                                                                                       \
                                                                                         \ \
   void ctECSFlagCacheAndHas##_NAME(ctECSFlagCache* cache) {                               \
      for (int i = 0; i < 255; i++) {                                                      \
         ctECSFlagCacheAndBit(cache,                                                       \
                              i,                                                           \
                              gComponentFactory##_NAME.entityToComponent[i] !=             \
                                CT_COMPONENT_INVALID);                                     \
      }                                                                                    \
   }                                                                                       \
                                                                                         \ \
   void ctECSFlagCacheAddHas##_NAME(ctECSFlagCache* cache) {                               \
      for (int i = 0; i < 255; i++) {                                                      \
         ctECSFlagCacheSetBit(cache,                                                       \
                              i,                                                           \
                              gComponentFactory##_NAME.entityToComponent[i] !=             \
                                CT_COMPONENT_INVALID);                                     \
      }                                                                                    \
   }                                                                                       \
                                                                                         \ \
   void ctECSFlagCacheSubtractHas##_NAME(ctECSFlagCache* cache) {                          \
      for (int i = 0; i < 255; i++) {                                                      \
         ctECSFlagCacheUnsetBit(cache,                                                     \
                                i,                                                         \
                                gComponentFactory##_NAME.entityToComponent[i] !=           \
                                  CT_COMPONENT_INVALID);                                   \
      }                                                                                    \
   } */
