// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* iSetTimerHandler (libkernel): set (or clear, with handler 0) the handler a counter calls `schedule` clocks
   after it starts. A running counter with a handler is (re)inserted into the alarm list. */
typedef struct {
    int timer_next;             /* 0x00 */
    int timer_previous;         /* 0x04 */
    int timer_key;              /* 0x08 */
    unsigned int timer_mode;    /* 0x0C */
    long timer_base_time;       /* 0x10 */
    long timer_base_count;      /* 0x18 */
    long timer_schedule;        /* 0x20 */
    void *callback_handler;     /* 0x28 */
    void *gp_value;             /* 0x2C */
    void *callback_handler_arg; /* 0x30 */
} Counter;
typedef struct { char pad[0x1C]; volatile int current_handling_timer_id; } TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */
long iGetTimerSystemTime(void);
void InsertAlarm(Counter *);
void UnlinkAlarm(Counter *);
void SetNextComp(long);

int iSetTimerHandler(int id, long schedule, void *handler, void *arg)
{
    Counter *counter = (Counter *)TIMER_ID_TO_PTR(id);
    TimerGlobal *timer;
    unsigned int mode;
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != counter->timer_key)
        return KE_EID;
    timer = &D_002C5A30;
    if (timer->current_handling_timer_id == id)
        return KE_EBUSY;
    mode = counter->timer_mode;
    if (mode & TIMER_MODE_HANDLER) {
        UnlinkAlarm(counter);
        mode = counter->timer_mode;
    }
    counter->callback_handler = handler;
    if (handler == 0) {
        counter->timer_mode = mode & ~TIMER_MODE_HANDLER;
    } else {
        register void *gp __asm__("$28");
        counter->timer_schedule = schedule;
        counter->timer_mode = mode | TIMER_MODE_HANDLER;
        counter->gp_value = gp;
        counter->callback_handler_arg = arg;
        if (*(volatile unsigned int *)&counter->timer_mode & TIMER_MODE_START)
            InsertAlarm(counter);
    }
    SetNextComp(iGetTimerSystemTime());
    return 0;
}
