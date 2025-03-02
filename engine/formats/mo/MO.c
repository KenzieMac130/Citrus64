/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "MO.h"

#include "codegen/engine/formats/mo/MO.c.gen.h"

ctResults ctMOReaderCreate(ctMOReader** readerOut, void* fileData, int fileSize) {
   ctAssert(readerOut);
   ctAssert(fileData);

   /* parse header */
   ctMOHeader tmpHeader;
   if (fileSize < sizeof(ctMOHeader)) { return CT_FAILURE_CORRUPTED_CONTENTS; }
   memcpy(&tmpHeader, fileData, sizeof(ctMOHeader));
   if (tmpHeader.magic != CT_MO_MAGIC) { return CT_FAILURE_CORRUPTED_CONTENTS; }
   if (tmpHeader.version != CT_MO_CUR_VER) { return CT_FAILURE_UNKNOWN_FORMAT; }

   /* allocate reader */
   ctMOReader tmpMoReader;
   ctMOReader* readerPtr;
   void* discard;
   uint32_t hashTableCapacity = ctNextPrime(tmpHeader.numStrings + 1);
   ctGroupAllocDesc groupAlloc[] = {
     {1, sizeof(ctMOReader), &discard},
     {1, sizeof(ctHashTableKey) * hashTableCapacity, (void**)&tmpMoReader.hashKeys},
     {1, sizeof(uint32_t) * hashTableCapacity, (void**)&tmpMoReader.hashValueOffsets},
   };
   readerPtr = (ctMOReader*)ctGroupAlloc(3, groupAlloc, NULL);
   ctAssert((void*)readerPtr == discard);

   /* load blob */
   tmpMoReader.blobSize = fileSize;
   tmpMoReader.blob = (uint8_t*)fileData;
   tmpMoReader.header = (ctMOHeader*)(&tmpMoReader.blob[0]);
   tmpMoReader.originalStringTable =
     (ctMOStringEntry*)(&tmpMoReader.blob[tmpHeader.originalOffset]);
   tmpMoReader.translatedStringTable =
     (ctMOStringEntry*)(&tmpMoReader.blob[tmpHeader.translatedOffset]);

   /* construct hash table (we could do this at compile time in the future) */
   tmpMoReader.hashTable = ctHashTableInit(hashTableCapacity, tmpMoReader.hashKeys);
   memset(tmpMoReader.hashValueOffsets, 0, sizeof(uint32_t) * hashTableCapacity);
   for (int32_t i = 0; i < tmpHeader.numStrings; i++) {
      const uint32_t originalOffset = tmpMoReader.originalStringTable[i].offset;
      const uint32_t newOffset = tmpMoReader.translatedStringTable[i].offset;
      const char* originalString = (const char*)(&tmpMoReader.blob[originalOffset]);
      const uint32_t hash = ctXXHash32String(originalString);
      uint32_t idx;
      CT_RETURN_FAIL_CLEAN(ctHashTableInsert(&tmpMoReader.hashTable, hash, &idx),
                           ctFree(readerPtr));
      tmpMoReader.hashValueOffsets[idx] = newOffset;
   }

   /* return reader */
   *readerPtr = tmpMoReader;
   *readerOut = readerPtr;
   return CT_SUCCESS;
}

void ctMOReaderFree(ctMOReader* reader) {
   ctFree(reader);
}

const char* ctMOFindTranslationHashed(ctMOReader* reader, uint32_t hash) {
   uint32_t idx;
   ctAssert(reader);
   if (ctErrorCheck(ctHashTableFindIdx(&reader->hashTable, hash, &idx))) { return NULL; }
   return (const char*)&reader->blob[reader->hashValueOffsets[idx]];
}

const char* ctMOFindTranslation(ctMOReader* reader, const char* original) {
   ctAssert(reader);
   uint32_t hash = ctXXHash32String(original);
   return ctMOFindTranslationHashed(reader, hash);
}