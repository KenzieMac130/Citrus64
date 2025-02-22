/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Utilities.h"

#if CT_BUILD_UNIT_TESTS
#include "engine/tests/UnitTester.h"
#endif

#include "codegen/engine/core/Entry.c.gen.h"

extern void _ctRandomHardwareInit();

void WaitForInput() {
   ctDebugLog("Press A on Controller 1 to continue...");
   console_render();
   joypad_poll();
   while (1) {
      if (joypad_get_buttons(JOYPAD_PORT_1).a) { break; }
      joypad_poll();
   }
}

int main(void) {
   kernel_init();
   _ctRandomHardwareInit();
   debug_init_usblog();
   debug_init_isviewer();
   joypad_init();
#if CT_BUILD_UNIT_TESTS
   console_init();
   console_set_debug(true);
#if CT_BUILD_WAIT_FOR_INPUT
   WaitForInput();
#endif
   return _ctUnitTestsMain();
#endif

   while (1) {};
   return 0;
}