// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* Init the alarm pool (ps2sdk: ForTimer_InitAlarm): chain all alarms into the free list. */
typedef struct Alarm { struct Alarm *alarm_next; int timer_counter_id; void *callback_handler; void *callback_handler_arg; } Alarm;
extern Alarm D_0044E300[TIMER_ALARM_COUNT];     /* g_AlarmBuf */
extern Alarm *D_0044E700;                       /* g_pFreeAlarm */

int func_0023A618(void)
{
    int i;
    D_0044E700 = D_0044E300;
    for (i = 0; i < TIMER_ALARM_COUNT; i++) D_0044E300[i].alarm_next = &D_0044E300[i + 1];
    D_0044E300[TIMER_ALARM_COUNT - 1].alarm_next = 0;
    return 0;
}
