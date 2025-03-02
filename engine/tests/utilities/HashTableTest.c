/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/Utilities.h"

#include "codegen/engine/tests/utilities/HashTableTest.c.gen.h"

#define KEY_COUNT 29
#define KEY_RM    4

void ctUnitTestHashTable() {
   ctHashTableKey keys[KEY_COUNT];
   uint32_t values[KEY_COUNT];

   ctHashTable table = ctHashTableInit(KEY_COUNT, keys);
   uint32_t idx;

   /* fill the hash table */
   for (uint32_t i = 0; i < KEY_COUNT; i++) {
      ctUnitTestAssert(ctHashTableInsert(&table, i, &idx) == CT_SUCCESS);
      values[idx] = i;
   }

   ctUnitTestAssert(ctHashTableRemove(&table, KEY_RM, &idx) == CT_SUCCESS);
   ctUnitTestAssert(values[idx] == KEY_RM); /* expected at this slot */
   ctUnitTestAssert(ctHashTableInsert(&table, 67009, &idx) == CT_SUCCESS);
   ctUnitTestAssert(values[idx] == KEY_RM); /* expected at this slot */
   values[idx] = 67009;
   ctUnitTestAssert(ctHashTableExists(&table, 67009));
   ctHashTableFindIdx(&table, 67009, &idx);
   ctUnitTestAssert(values[idx] == 67009);
   for (int i = 0; i < 3; i++) {
      ctHashTableRemove(&table, KEY_COUNT - 1 - i, NULL);
   }
   ctHashTableFindIdx(&table, 67009, &idx);
   values[idx] = 3020000;
   ctHashTableFindIdx(&table, 67009, &idx);
   ctUnitTestAssert(values[idx] == 3020000);

   for (int i = 11; i < 17; i++) {
      ctHashTableRemove(&table, i, NULL);
   }

   ctUnitTestAssert(ctHashTableInsert(&table, 47844847, &idx) == CT_SUCCESS);
   values[idx] = 47844847;
   ctUnitTestAssert(ctHashTableExists(&table, 47844847));
   ctHashTableFindIdx(&table, 47844847, &idx);
   values[idx] = 478448455;
   ctHashTableFindIdx(&table, 47844847, &idx);
   ctUnitTestAssert(values[idx] == 478448455);

   for (uint32_t i = 0; i < KEY_COUNT; i++) {
      // ctDebugLog("H:%u V:%u L:%hu N:%hu", keys[i].hash, values[i], keys[i].last,
      // keys[i].next);
   }
}