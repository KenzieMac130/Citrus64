/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Utilities.h"

#include "engine/core/EngineCore.h"

#if CT_BUILD_UNIT_TESTS
#include "engine/tests/UnitTester.h"
#endif

#include "codegen/engine/core/Entry.c.gen.h"

extern void _ctRandomHardwareInit();

#if CT_BUILD_WAIT_FOR_INPUT
void WaitForInput() {
   console_init();
   console_set_render_mode(RENDER_AUTOMATIC);
   ctDebugLog("Press A on Controller 1 to continue...");
   joypad_poll();
   while (1) {
      if (joypad_get_buttons(JOYPAD_PORT_1).a) { break; }
      joypad_poll();
   }
   console_close();
}
#endif

int main(void) {
/* Hardware Setup */
#if CT_ALLOW_MULTI_THREADING
   kernel_init();
#endif
   _ctRandomHardwareInit();
   dfs_init(DFS_DEFAULT_LOCATION);
   debug_init_usblog();
   debug_init_isviewer();
   joypad_init();
   rdpq_init();

#if CT_BUILD_WAIT_FOR_INPUT
   WaitForInput();
#endif

#if CT_BUILD_UNIT_TESTS
   return _ctUnitTestsMain();
#endif

   ctEngineIgnite();
   ctEngineLoop();
   ctEngineShutdown();
   return 0;
}