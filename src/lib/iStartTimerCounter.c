// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* iStartTimerCounter (libkernel): start a counter at the current system time; one with a handler goes on the
   alarm list. Returns 1 if it was already running. */
typedef struct { int timer_next; int timer_previous; int timer_key; int timer_mode; long timer_base_time; } Counter;
typedef struct { char pad[0x1C]; volatile int current_handling_timer_id; } TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */
long iGetTimerSystemTime(void);
void InsertAlarm(Counter *);
void SetNextComp(long);

int iStartTimerCounter(int id)
{
    Counter *counter = (Counter *)TIMER_ID_TO_PTR(id);
    long now;
    TimerGlobal *timer;
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != counter->timer_key)
        return KE_EID;
    timer = &D_002C5A30;
    if (timer->current_handling_timer_id == id)
        return KE_EBUSY;
    if (counter->timer_mode & TIMER_MODE_START)
        return 1;
    now = iGetTimerSystemTime();
    counter->timer_base_time = now;
    counter->timer_mode |= TIMER_MODE_START;
    if (counter->timer_mode & TIMER_MODE_HANDLER) {
        InsertAlarm(counter);
        SetNextComp(now);
    }
    return 0;
}
