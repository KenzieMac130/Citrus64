/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Utilities.h"

#if CT_BUILD_UNIT_TESTS
#include "engine/tests/UnitTester.h"
#endif

#include "codegen/engine/core/Entry.c.gen.h"

extern void _ctRandomHardwareInit();

int main(void) {
   _ctRandomHardwareInit();
   debug_init_usblog();
   debug_init_isviewer();
#if CT_BUILD_UNIT_TESTS
   console_init();
   console_set_debug(true);
   return _ctUnitTestsMain();
#endif

   while (1) {};
   return 0;
}