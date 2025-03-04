/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file MO.h

Translation file format
https://www.gnu.org/software/gettext/manual/html_node/MO-Files.html
*/

#include "engine/utilities/Utilities.h"

#include "codegen/engine/formats/mo/MO.h.gen.h"

#define CT_MO_MAGIC   0x950412de
#define CT_MO_CUR_VER 0

typedef struct {
   int32_t magic;
   int32_t version;
   int32_t numStrings;
   int32_t originalOffset;
   int32_t translatedOffset;
   int32_t _unused0; /* GNU baked hash table size */
   int32_t _unused1; /* GNU baked hash table offset */
} ctMOHeader;

typedef struct {
   int32_t length;
   int32_t offset;
} ctMOStringEntry;

typedef struct {
   ctMOHeader* header;
   ctMOStringEntry* originalStringTable;
   ctMOStringEntry* translatedStringTable;

   ctHashTable hashTable;
   ctHashTableKey* hashKeys;
   uint32_t* hashValueOffsets;

   uint8_t* blob;
   size_t blobSize;
} ctMOReader;

/*! @brief Create a MO file reader from a file of known size */
CT_ENGINE_API ctResults ctMOReaderCreate(ctMOReader** readerOut, void* fileData, int fileSize);
/*! @brief Free the MO file */
CT_ENGINE_API void ctMOReaderFree(ctMOReader* reader);

/*! @brief Find a translation that matches a string */
CT_ENGINE_API const char* ctMOFindTranslation(ctMOReader* reader, const char* original);

/*! @brief Find a translation that matches a string hashed with xxhash32 */
CT_ENGINE_API const char* ctMOFindTranslationHashed(ctMOReader* reader, uint32_t hash);