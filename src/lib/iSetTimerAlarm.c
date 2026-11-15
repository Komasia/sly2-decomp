// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "ee_kernel.h"
/* iSetTimerAlarm (libkernel): interrupt-context SetTimerAlarm: run `handler` once after `clocks` bus clocks. */
typedef struct Alarm {
    struct Alarm *alarm_next;
    volatile int timer_counter_id;
    void *callback_handler;
    void *callback_handler_arg;
} Alarm;
extern Alarm *D_0044E700;       /* g_pFreeAlarm */
int iAllocTimerCounter(void);
int iSetTimerHandler(int, long, void *, void *);
int iStartTimerCounter(int);
int func_0023A668(int, int, int, Alarm *);  /* AlarmHandler */

static inline Alarm *AllocAlarm(void)
{
    Alarm *alarm = D_0044E700;
    if (alarm)
        D_0044E700 = alarm->alarm_next;
    return alarm;
}

int iSetTimerAlarm(long clocks, void *handler, void *arg)
{
    Alarm *alarm;
    int id;
    if (handler == 0)
        return KE_EINVAL;
    alarm = AllocAlarm();
    if (alarm == 0)
        return KE_ETIMER;
    id = iAllocTimerCounter();
    if (id >= 0) {
        alarm->callback_handler = handler;
        alarm->callback_handler_arg = arg;
        alarm->timer_counter_id = id;
        iSetTimerHandler(id, clocks, func_0023A668, alarm);
        iStartTimerCounter(id);
        return ((int)alarm << 4) | (id & 0xFE) | 1;
    }
    {
        Alarm *head = D_0044E700;   /* give the alarm back */
        D_0044E700 = alarm;
        alarm->alarm_next = head;
        alarm->timer_counter_id = 0;
    }
    return id;
}
