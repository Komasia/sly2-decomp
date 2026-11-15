// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* SetTimerAlarm (libkernel): call `handler(id, scheduled, actual, arg)` once `clocks` bus clocks from now.
   Takes an alarm from the pool, gives it a running timer counter whose handler is AlarmHandler, and returns
   the alarm id. Thread-safe version of iSetTimerAlarm. */
typedef struct Alarm {
    struct Alarm *alarm_next;   /* free-list link */
    volatile int timer_counter_id;
    void *callback_handler;
    void *callback_handler_arg;
} Alarm;
extern Alarm *D_0044E700;       /* g_pFreeAlarm */
int DIntr(void);
int EIntr(void);
int AllocTimerCounter(void);
int SetTimerHandler(int, long, void *, void *);
int func_0023A3A0(int);         /* StartTimerCounter */
int func_0023A668(int, int, int, Alarm *);  /* AlarmHandler */

static inline Alarm *AllocAlarm(void)
{
    Alarm *alarm = D_0044E700;
    if (alarm)
        D_0044E700 = alarm->alarm_next;
    return alarm;
}

int SetTimerAlarm(long clocks, void *handler, void *arg)
{
    Alarm *alarm;
    int id;
    int intr;
    if (handler == 0)
        return KE_EINVAL;
    intr = DIntr();
    alarm = AllocAlarm();
    if (alarm == 0) {
        if (intr)
            EIntr();
        return KE_ETIMER;
    }
    id = AllocTimerCounter();
    if (id < 0) {
        Alarm *head = D_0044E700;   /* give the alarm back */
        D_0044E700 = alarm;
        alarm->alarm_next = head;
        alarm->timer_counter_id = 0;
        if (intr)
            EIntr();
        return id;
    }
    alarm->callback_handler = handler;
    alarm->callback_handler_arg = arg;
    alarm->timer_counter_id = id;
    SetTimerHandler(id, clocks, func_0023A668, alarm);
    func_0023A3A0(id);
    if (intr)
        EIntr();
    return ((int)alarm << 4) | (id & 0xFE) | 1;
}
