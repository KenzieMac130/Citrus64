#include "engine/utilities/Utilities.h"

#include "codegen/game/modules/example/test.c.gen.h"

#define MY_STRING_HASH  = CT_XXH32_STRING(My_String, "My, \\ String\"");
#define MY_STRING_HASH1 = CT_XXH32_STRING(My_String2, "My, Ekfekf \\ String333\"");

void dooot() {
   ctVec3 myValue = ctVec3Zero();
   ctVec3Add(&myValue, ctVec3Make(0.0f, 1.0f, 3.0f));
}