// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* SetNextComp (libkernel timer): program the T2 compare register for the next alarm. Alarms due within
   TIMER_COMP_MARGIN of each other are merged; if the next one is (nearly) due already, fire it right away. */
typedef struct Counter {
    struct Counter *timer_next;     /* 0x00 */
    int timer_previous;             /* 0x04 */
    long timer_key_mode;            /* 0x08 timer_key, timer_mode */
    unsigned long timer_base_time;  /* 0x10 */
    unsigned long timer_base_count; /* 0x18 */
    unsigned long timer_schedule;   /* 0x20 */
} Counter;
typedef struct {
    char pad[0x18];
    Counter *timer_counter_buf_alarm;   /* 0x18 alarm list */
    int current_handling_timer_id;      /* 0x1C */
} TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */
void SetT2_COMP(int);   /* SetT2_COMP */
void SetT2_MODE(int);   /* SetT2_MODE */

void SetNextComp(unsigned long now)
{
    Counter *counter;
    unsigned long next, fire;
    unsigned int mode;

    counter = D_002C5A30.timer_counter_buf_alarm;
    if (D_002C5A30.current_handling_timer_id >= 0)
        return;
    mode = T2_MODE;
    if (counter == 0) {
        SetT2_COMP(0);
        SetT2_MODE(mode & ~T_MODE_OVFF);
        return;
    }
    next = counter->timer_schedule + counter->timer_base_time - counter->timer_base_count;
    counter = counter->timer_next;
    while (counter != 0) {
        fire = counter->timer_schedule + counter->timer_base_time - counter->timer_base_count;
        if (fire < next + TIMER_COMP_MARGIN)
            next = fire;
        else
            break;
        counter = counter->timer_next;
    }
    if ((long)(next - now) < TIMER_COMP_MARGIN) {
        SetT2_COMP(T2_COUNT + (int)((unsigned long)TIMER_COMP_MARGIN >> ((mode & T_MODE_CLKS) * 4)));
        SetT2_MODE(mode & ~T_MODE_OVFF);
        return;
    }
    SetT2_MODE(mode & ~T_MODE_OVFF);
    SetT2_COMP(next >> ((mode & T_MODE_CLKS) * 4));
}
