/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/utilities/Common.h"

#if CT_BUILD_UNIT_TESTS
#include "engine/tests/UnitTester.h"
#endif

#include "codegen/engine/core/Entry.c.gen.h"

int main(void)
{
    console_init();
    debug_init_usblog();
    debug_init_isviewer();
    console_set_debug(true);
#if CT_BUILD_UNIT_TESTS
    return _ctUnitTestsMain();
#endif

    while(1){};
    return 0;
}