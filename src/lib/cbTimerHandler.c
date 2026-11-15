// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* cbTimerHandler (libkernel timer): INTC_TIM2 interrupt handler. On a compare event, run every alarm that is
   due: its handler returns 0 (stop), -1 (free the counter) or the clocks until it should run again. Then
   program the next compare. The handler's $gp is loaded from the counter (asm); the inline GetTime is
   iGetTimerSystemTime; the overflow count and used-counter count are volatile as in the original. */
typedef struct Counter {
    struct Counter *timer_next;     /* 0x00 */
    int timer_previous;             /* 0x04 */
    int timer_key;                  /* 0x08 */
    unsigned int timer_mode;        /* 0x0C */
    unsigned long timer_base_time;  /* 0x10 */
    unsigned long timer_base_count; /* 0x18 */
    unsigned long timer_schedule;   /* 0x20 */
    unsigned long (*callback_handler)(int, unsigned long, unsigned long, void *, void *);   /* 0x28 */
    void *gp_value;                 /* 0x2C */
    void *callback_handler_arg;     /* 0x30 */
} Counter;
typedef struct {
    volatile unsigned long timer_handled_count; /* 0x00 overflow count */
    int pad8[2];
    volatile int timer_counter_used;    /* 0x10 */
    Counter *timer_counter_buf_free;    /* 0x14 */
    Counter *timer_counter_buf_alarm;   /* 0x18 */
    int current_handling_timer_id;      /* 0x1C */
} TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */
void SetT2_MODE(unsigned int);   /* SetT2_MODE */
Counter *UnlinkAlarm(Counter *);
void InsertAlarm(Counter *);
void SetNextComp(unsigned long);

static inline unsigned long GetTime(void)
{
    unsigned int count, mode;
    count = T2_COUNT;
    mode = T2_MODE;
    if (mode & T_MODE_OVFF) {
        D_002C5A30.timer_handled_count++;
        SetT2_MODE(mode & ~T_MODE_EQUF);
        count = T2_COUNT;
    }
    return ((D_002C5A30.timer_handled_count << 16) | count) << ((mode & T_MODE_CLKS) * 4);
}

int cbTimerHandler(int cause, void *arg, void *addr)
{
    Counter *counter, *next;
    unsigned long now, fire, ret;

    if (T2_MODE & T_MODE_EQUF) {
        counter = D_002C5A30.timer_counter_buf_alarm;
        while (counter) {
            fire = counter->timer_schedule + counter->timer_base_time - counter->timer_base_count;
            now = GetTime();
            if (now < fire)
                break;
            next = UnlinkAlarm(counter);
            {
                unsigned long count = now + counter->timer_base_count - counter->timer_base_time;
                D_002C5A30.current_handling_timer_id = ((unsigned int)counter << 4) | counter->timer_key;
                __asm__ __volatile__("lw $28, %0" : : "m"(counter->gp_value));
                ret = counter->callback_handler(((unsigned int)counter << 4) | counter->timer_key,
                                                counter->timer_schedule, count,
                                                counter->callback_handler_arg, addr);
            }
            if (ret == 0) {
                counter->timer_mode &= ~TIMER_MODE_HANDLER;
            } else if (ret == (unsigned long)-1) {
                counter->timer_key = 0;
                counter->timer_mode = 0;
                counter->timer_next = D_002C5A30.timer_counter_buf_free;
                D_002C5A30.timer_counter_buf_free = counter;
                D_002C5A30.timer_counter_used--;
            } else {
                if (ret < TIMER_MIN_RESCHEDULE)
                    ret = TIMER_MIN_RESCHEDULE;
                counter->timer_schedule += ret;
                InsertAlarm(counter);
            }
            counter = next;
        }
    }
    D_002C5A30.current_handling_timer_id = -1;
    SetNextComp(GetTime());
    GetTime();
    __asm__ __volatile__("sync\n\tei");
    return 0;
}
