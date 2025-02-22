/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file HashTable.h
Hash table for building (almost) O(1) data structures like dictionaries and sets
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

/*! @brief Initialize a hash table and its key buffer
   @warning capacity must be a prime number
   @warning the memory lifetime of keyBuffer must be the same as the table
   @param capacity amount of ctHashTableKey in keyBuffer
   @param keyBuffer buffer of ctHashTableKey the size of capacity

   Example of a Set
   @code
   // creation
   ctHashTableKey keys[257];
   ctHashTable table;
   ...
   table = ctHashTableInit(257, &keys);

   // insertion
   CT_RETURN_FAIL(ctHashTableInsert(&table, ctXXHash32String("Foo"), NULL));

   // getting
   bool exists = ctHashTableExists(&table, ctXXHash32String("Foo"));

   // deletion
   CT_RETURN_FAIL(ctHashTableRemove(&table, ctXXHash32String("Foo"), NULL));

   @endcode

   Example of a Dictionary
   @code
   // creation
   ctHashTableKey keys[31];
   MyObjectStruct values[31];
   ctHashTable table;
   ...
   table = ctHashTableInit(31, &keys);

   // insertion
   uint32_t idx;
   CT_RETURN_FAIL(ctHashTableInsert(&table, MakeKey("Foo", 64), &idx));
   values[idx].name = "Foo";
   values[idx].value = 64;
   values[idx].data = MakeData(128);

   // getting
   CT_RETURN_FAIL(ctHashTableFindIdx(&table, MakeKey("Foo", 64), &idx));
   UseData(value[idx].data);

   // deletion
   CT_RETURN_FAIL(ctHashTableRemove(&table, MakeKey("Foo", 64), &idx));
   FreeData(values[idx].data);
   @endcode
*/
ctHashTable ctHashTableInit(uint32_t capacity, ctHashTableKey* keyBuffer);

/*! @brief Insert a key into the table and track its index
   @warning A key MUST NOT equal UINT32_MAX
*/
ctResults ctHashTableInsert(ctHashTable* table, uint32_t key, uint32_t* outIdx);

/*! @brief Remove a key from the table and "free up" its index
   @warning A key MUST NOT equal UINT32_MAX
*/
ctResults ctHashTableRemove(ctHashTable* table, uint32_t key, uint32_t* outIdx);

/*! @brief Check if a key exists in the hash table */
bool ctHashTableExists(ctHashTable* table, uint32_t key);

/*! @brief Find the index of a key

   Can be used to index into a secondary list. By default a lone hash table is just a set
   but by using a secondary table or even another list of hash tables you can create
   much more complex data structures

   @warning A key MUST NOT equal UINT32_MAX
*/
ctResults ctHashTableFindIdx(ctHashTable* table, uint32_t key, uint32_t* outIdx);

/*! @brief Clear the hash table */
void ctHashTableClear(ctHashTable* table);