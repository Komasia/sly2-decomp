// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* InsertAlarm (libkernel timer): insert a counter into the alarm list, kept sorted by the system time at which
   it fires (schedule + base_time - base_count). */
typedef struct Counter {
    struct Counter *timer_next;     /* 0x00 */
    struct Counter *timer_previous; /* 0x04 */
    int timer_key;                  /* 0x08 */
    unsigned int timer_mode;        /* 0x0C */
    unsigned long timer_base_time;  /* 0x10 */
    unsigned long timer_base_count; /* 0x18 */
    unsigned long timer_schedule;   /* 0x20 */
} Counter;
typedef struct { int pad[6]; Counter *timer_counter_buf_alarm; /* 0x18 */ } TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */

void InsertAlarm(Counter *counter)
{
    Counter *prev = 0, *cur;
    unsigned long fire = counter->timer_schedule + counter->timer_base_time - counter->timer_base_count;
    cur = D_002C5A30.timer_counter_buf_alarm;
    while (cur) {
        if (fire < cur->timer_schedule + cur->timer_base_time - cur->timer_base_count) break;
        prev = cur;
        cur = prev->timer_next;
    }
    counter->timer_previous = prev;
    counter->timer_next = cur;
    if (cur) cur->timer_previous = counter;
    if (prev) prev->timer_next = counter;
    else D_002C5A30.timer_counter_buf_alarm = counter;
}
