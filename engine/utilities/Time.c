/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
#include "Time.h"

#include "codegen/engine/utilities/Time.c.gen.h"

ctStopwatch ctStopwatchInit() {
   ctStopwatch result;
   result.currentHardwareTick = get_ticks();
   result.lastHardwareTick = result.currentHardwareTick;
   return result;
}

void ctStopwatchNextLap(ctStopwatch* stopwatch) {
   stopwatch->lastHardwareTick = stopwatch->currentHardwareTick;
   stopwatch->currentHardwareTick = get_ticks();
}

float ctStopwatchGetDeltaTime(const ctStopwatch* stopwatch) {
   return (float)(stopwatch->currentHardwareTick - stopwatch->lastHardwareTick) /
          (float)TICKS_PER_SECOND;
}