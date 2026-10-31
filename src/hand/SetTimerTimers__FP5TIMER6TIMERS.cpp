/* SetTimerTimers (Sly 1 screen.c): change the timer's state and note when. Sly 2 stamps it with the real-time
 * clock (Sly 1: g_clock.t). */
#include "screen.h"
#include "clock.h"

void SetTimerTimers(TIMER *ptimer, TIMERS timers)
{
    if (ptimer->timers != timers)
    {
        ptimer->timers = timers;
        ptimer->tTimers = g_clock.tReal;
    }
}
