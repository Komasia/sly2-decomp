// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* UnlinkAlarm (libkernel timer): remove a counter from the alarm list; returns the counter that followed it. */
typedef struct Counter { struct Counter *timer_next; struct Counter *timer_previous; } Counter;
typedef struct { int pad[6]; Counter *timer_counter_buf_alarm; /* 0x18 */ } TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */

Counter *UnlinkAlarm(Counter *counter)
{
    Counter *next = counter->timer_next;
    if (counter->timer_previous) counter->timer_previous->timer_next = next;
    else D_002C5A30.timer_counter_buf_alarm = next;
    if (next) next->timer_previous = counter->timer_previous;
    counter->timer_previous = 0;
    return next;
}
