/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "HashTable.h"

#include "Math.h"

#include "codegen/engine/utilities/HashTable.c.gen.h"

ctHashTable ctHashTableInit(uint32_t capacity, ctHashTableKey* keyBuffer) {
   ctAssert("Capacity must be prime" && ctIsPrime(capacity));
   ctAssert("Capacity must be under 65536" && capacity < UINT16_MAX);
   ctAssert(keyBuffer);
   ctHashTable result;
   result.capacity = (uint16_t)capacity;
   result.keys = keyBuffer;
   ctHashTableClear(&result);
   return result;
}

uint32_t _ctHashTableFindIdx(ctHashTable* table, uint32_t key) {
   ctAssert(table);
   ctAssert(key != UINT32_MAX);
   uint32_t idx = key % (uint32_t)table->capacity;
   while (table->keys[idx].hash != key) {
      idx = (uint32_t)table->keys[idx].next;
      if (idx == UINT16_MAX) { return UINT32_MAX; }
   }
   return idx;
}

ctResults ctHashTableFindIdx(ctHashTable* table, uint32_t key, uint32_t* outIdx) {
   *outIdx = _ctHashTableFindIdx(table, key);
   if (*outIdx == UINT32_MAX) { return CT_FAILURE_NOT_FOUND; }
   return CT_SUCCESS;
}

ctResults ctHashTableInsert(ctHashTable* table, uint32_t key, uint32_t* outIdx) {
   ctAssert(table);
   ctAssert(key != UINT32_MAX);
   ctHashTableKey result;
   result.hash = key;
   result.next = UINT16_MAX;
   result.last = UINT16_MAX;
   uint32_t idx = key % (uint32_t)table->capacity;
   uint32_t jumpKeyIdx = UINT32_MAX; /* last key we colided with */
   /* loop until we find an open slot */
   for (uint16_t retry = 0; retry < table->capacity; retry++) {
      ctHashTableKey* testKey = &table->keys[idx];
      if (testKey->hash == UINT32_MAX) { break; } /* open slot */
      /* a duplicate of the parent was found (fail to insert) */
      if (testKey->hash == key) { return CT_FAILURE_DUPLICATE_ENTRY; }
      if (jumpKeyIdx == UINT32_MAX) { /* store this key as a collision */
         jumpKeyIdx = idx;
      }
      idx = (key + retry) % (uint32_t)table->capacity; /* retry the next possible slot */
      if (retry == table->capacity - 1) {
         return CT_FAILURE_OUT_OF_MEMORY;
      } /* bail on end */
   }
   /* a collision happened, build a relationship */
   if (jumpKeyIdx != UINT32_MAX) {
      /* find the last key on the chain */
      while (table->keys[jumpKeyIdx].next != UINT16_MAX) {
         jumpKeyIdx = table->keys[jumpKeyIdx].next;
      }
      table->keys[jumpKeyIdx].next = (uint16_t)idx;
      table->keys[idx].last = (uint16_t)jumpKeyIdx;
      result.last = (uint16_t)jumpKeyIdx;
   }
   table->keys[idx] = result;
   if (outIdx) { *outIdx = idx; }
   return CT_SUCCESS;
}

ctResults ctHashTableRemove(ctHashTable* table, uint32_t key, uint32_t* outIdx) {
   ctAssert(table);
   ctAssert(key != UINT32_MAX);
   uint32_t idx = _ctHashTableFindIdx(table, key);
   if (idx == UINT32_MAX) { return CT_FAILURE_NOT_FOUND; }
   if (table->keys[idx].next != UINT16_MAX) { /* bridge last to next */
      table->keys[table->keys[idx].next].last = table->keys[idx].last;
   }
   if (table->keys[idx].last != UINT16_MAX) { /* bridge next to last */
      table->keys[table->keys[idx].last].next = table->keys[idx].next;
   }
   table->keys[idx].hash = UINT32_MAX; /* erase at index */
   table->keys[idx].last = UINT16_MAX;
   table->keys[idx].next = UINT16_MAX;
   if (outIdx) { *outIdx = idx; }
   return CT_SUCCESS;
}

bool ctHashTableExists(ctHashTable* table, uint32_t key) {
   ctAssert(table);
   ctAssert(key != UINT32_MAX);
   return (_ctHashTableFindIdx(table, key) != UINT32_MAX);
}

void ctHashTableClear(ctHashTable* table) {
   ctAssert(table);
   for (uint32_t i = 0; i < table->capacity; i++) {
      table->keys[i].hash = UINT32_MAX;
      table->keys[i].next = UINT16_MAX;
      table->keys[i].last = UINT16_MAX;
   }
}