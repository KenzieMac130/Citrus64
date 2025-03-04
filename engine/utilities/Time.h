/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */
/*! @file Time.h

Time related utilities
*/
#pragma once
#include "Common.h"

#include "codegen/engine/utilities/Time.h.gen.h"

/*! @brief Keeps track of time at a hardware level

This doesn't work off of game ticks but rather the
amount of real-world time that has passed between "laps"
So the timer is dependent on quirks in hardware and nondeterministic

This is perfect for performance profiling but non-ideal for gameplay

If you want to keep track of game time you should accumulate the
game tick's/update's delta time instead. */
typedef struct {
   uint64_t lastHardwareTick;
   uint64_t currentHardwareTick;
} ctStopwatch;

/*! @brief Initialize the stopwatch and start the clock immediately */
CT_ENGINE_API ctStopwatch ctStopwatchInit();

/*! @brief Progress the stopwatch to the next lap (or end the timer) */
CT_ENGINE_API void ctStopwatchNextLap(ctStopwatch* stopwatch);

/*! @brief Get the delta time of the last lap in real-world time */
CT_ENGINE_API float ctStopwatchGetDeltaTime(const ctStopwatch* stopwatch);