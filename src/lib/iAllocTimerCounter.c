// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder
#include "ee_kernel.h"
/* iAllocTimerCounter (libkernel): take a counter from the free list, reset it and give it a fresh key.
   Returns its timer id ((counter << 4) | key), or KE_ETIMER when none is left. */
typedef struct Counter {
    struct Counter *timer_next;     /* 0x00 */
    int timer_previous;             /* 0x04 */
    volatile int timer_key;         /* 0x08 */
    int timer_mode;                 /* 0x0C */
    int timer_base_time[2];         /* 0x10 */
    long timer_base_count;          /* 0x18 */
    int timer_schedule[2];          /* 0x20 */
    void *callback_handler;         /* 0x28 */
} Counter;
typedef struct {
    int timer_handled_count[2];     /* 0x00 */
    int intc_handler;               /* 0x08 */
    volatile int timer_counter_total;   /* 0x0C allocation sequence, feeds the key */
    int timer_counter_used;         /* 0x10 */
    Counter *timer_counter_buf_free;    /* 0x14 */
} TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */

int iAllocTimerCounter(void)
{
    TimerGlobal *timer = &D_002C5A30;
    Counter *counter = timer->timer_counter_buf_free;
    if (counter != 0) {
        timer->timer_counter_used++;
        counter->callback_handler = 0;
        counter->timer_mode = 0;
        timer->timer_counter_buf_free = counter->timer_next;
        counter->timer_base_count = 0;
        timer->timer_counter_total++;
        counter->timer_key = ((timer->timer_counter_total << 1) & 0x3FE) | 1;
        return ((int)counter << 4) | counter->timer_key;
    }
    return KE_ETIMER;
}
