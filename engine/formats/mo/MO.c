/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "MO.h"

#include "codegen/engine/formats/mo/MO.c.gen.h"

ctResults ctMOReaderAllocFromFile(ctMOReader** readerOut, FILE* fp, int fileSize) {
   ctAssert(readerOut);
   ctAssert(fp);

   /* parse header */
   ctMOHeader tmpHeader;
   if (fileSize < sizeof(ctMOHeader)) { return CT_FAILURE_CORRUPTED_CONTENTS; }
   fread(&tmpHeader, sizeof(ctMOHeader), 1, fp);
   rewind(fp);
   if (tmpHeader.magic != CT_MO_MAGIC) { return CT_FAILURE_CORRUPTED_CONTENTS; }
   if (tmpHeader.version != CT_MO_CUR_VER) { return CT_FAILURE_UNKNOWN_FORMAT; }

   /* allocate reader */
   ctMOReader tmpMoReader;
   void* readerPtr;
   void* discard;
   uint32_t hashTableCapacity = ctNextPrime(tmpHeader.numStrings);
   ctGroupAllocDesc groupAlloc[] = {
     {1, sizeof(ctMOReader), &discard},
     {1, fileSize, (void**)&tmpMoReader.blob},
     {1, sizeof(ctHashTableKey) * hashTableCapacity, (void**)&tmpMoReader.hashKeys},
     {1, sizeof(uint32_t) * hashTableCapacity, (void**)&tmpMoReader.hashValueOffsets},
   };
   readerPtr = ctGroupAlloc(4, groupAlloc, NULL);
   ctAssert(readerPtr == discard);

   /* load blob */
   tmpMoReader.blobSize = fileSize;
   fread(tmpMoReader.blob, fileSize, 1, fp);
   tmpMoReader.header = (ctMOHeader*)(&tmpMoReader.blob[0]);
   tmpMoReader.originalStringTable =
     (ctMOStringEntry*)(&tmpMoReader.blob[tmpHeader.originalOffset]);
   tmpMoReader.translatedStringTable =
     (ctMOStringEntry*)(&tmpMoReader.blob[tmpHeader.translatedOffset]);

   /* construct hash table (we could do this at compile time in the future) */
   tmpMoReader.hashTable = ctHashTableInit(hashTableCapacity, tmpMoReader.hashKeys);
   for (int32_t i = 0; i < tmpHeader.numStrings; i++) {
      const uint32_t offset = tmpMoReader.originalStringTable[i].offset;
      const uint32_t hash = ctXXHash32String((const char*)(&tmpMoReader.blob[offset]));
      uint32_t idx;
      CT_RETURN_FAIL_CLEAN(ctHashTableInsert(&tmpMoReader.hashTable, hash, &idx),
                           ctFree(readerPtr));
      tmpMoReader.hashValueOffsets[idx] = offset;
   }

   /* return reader */
   *readerOut = readerPtr;
   **readerOut = tmpMoReader;
   return CT_SUCCESS;
}

void ctMOReaderFree(ctMOReader* reader) {
   ctFree(reader);
}

const char*
ctMOFindTranslationHashed(ctMOReader* reader, uint32_t hash, const char* original) {
   const ctMOStringEntry* translatedStringTable = reader->translatedStringTable;
   uint32_t idx;
   if (ctErrorCheck(ctHashTableFindIdx(&reader->hashTable, hash, &idx))) {
      return NULL;
   }
   return (const char*)&reader->blob[translatedStringTable[idx].offset];
}

const char* ctMOFindTranslation(ctMOReader* reader, const char* original) {
   ctAssert(reader);
   uint32_t hash = ctXXHash32String(original);
   return ctMOFindTranslationHashed(reader, hash, original);
}