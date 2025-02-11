/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file HashTable.h
Hash table for dictionaries and sets
*/
#pragma once

#include "Common.h"

#include "codegen/engine/utilities/HashTable.h.gen.h"

/*! @brief Key entry for ctHashTable */
typedef struct {
   uint32_t hash;
   uint16_t next;
   uint16_t last;
} ctHashTableKey;

/*! @brief Contains the state for hash table functions */
typedef struct {
   ctHashTableKey* keys;
   uint16_t capacity;
} ctHashTable;

ctHashTable ctHashTableInit(uint32_t capacity, ctHashTableKey* keyBuffer);

ctResults ctHashTableInsert(ctHashTable* table, uint32_t key, uint32_t* outIdx);
ctResults ctHashTableRemove(ctHashTable* table, uint32_t key, uint32_t* outIdx);

bool ctHashTableExists(ctHashTable* table, uint32_t key);
// todo: move to ctResults approach with outIdx
uint32_t ctHashTableFindIdx(ctHashTable* table, uint32_t key);

void ctHashTableClear(ctHashTable* table);