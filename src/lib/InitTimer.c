// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -Os -G0
// SLY2_ASM: gnu-reorg
#include "ee_kernel.h"
/* InitTimer (libkernel): set up the timer-2 counter system: build the free list of counters, init the alarm
   pool, hook the INTC_TIM2 interrupt and start T2 in `prescale` mode with compare/overflow interrupts. */
typedef struct Counter { struct Counter *timer_next; int pad[15]; } Counter;   /* 64 bytes */
typedef struct {
    long timer_handled_count;   /* 0x00 overflow count */
    int intc_handler;           /* 0x08 INTC handler id, <0 = not initialised */
    int timer_counter_total;    /* 0x0C */
    int timer_counter_used;     /* 0x10 */
    Counter *timer_counter_buf_free;    /* 0x14 */
} TimerGlobal;
extern TimerGlobal D_002C5A30;  /* g_Timer */
extern Counter D_0044C300[TIMER_COUNTER_COUNT];    /* g_CounterBuf */
void cbTimerHandler(void);
void *s1_memset(void *, int, int) asm("memset");
void func_0023A618(void);       /* init the alarm pool */
int func_00234710(int, void *, int, void *);   /* AddIntcHandler2 (syscall 0x10) */
int DIntr(void);
void func_00239AB0(int);        /* SetT2_COUNT */
void func_00239AC0(int);        /* SetT2_MODE */
void func_00239AD0(int);        /* SetT2_COMP */
int func_00235178(int);         /* EnableIntc */
int EIntr(void);

int InitTimer(int prescale)
{
    TimerGlobal *timer = &D_002C5A30;
    Counter *counter;
    int i, handler, intr;
    unsigned int mode;
    if (timer->intc_handler >= 0)
        return KE_EINIT;
    timer->timer_handled_count = 0;
    timer->timer_counter_used = 0;
    s1_memset(D_0044C300, 0, sizeof(D_0044C300));
    timer->timer_counter_buf_free = D_0044C300;
    {
        Counter *next;
        i = TIMER_COUNTER_COUNT - 1;
        counter = &D_0044C300[TIMER_COUNTER_COUNT - 1];
        next = &D_0044C300[TIMER_COUNTER_COUNT];
        for (; i >= 0; i--) {
            counter->timer_next = next;
            counter--;
            next--;
        }
    }
    D_0044C300[TIMER_COUNTER_COUNT - 1].timer_next = 0;
    func_0023A618();
    handler = func_00234710(INTC_TIM2, cbTimerHandler, 0, 0);
    if (handler < 0)
        return KE_EINT_HANDLER;
    D_002C5A30.intc_handler = handler;
    intr = DIntr();
    mode = T2_MODE;
    mode = (mode & ~T_MODE_CLKS) | prescale;
    mode |= T_MODE_CMPE | T_MODE_OVFE;
    if (!(mode & T_MODE_CUE)) {
        func_00239AB0(0);
        mode |= T_MODE_OVFF | T_MODE_EQUF | T_MODE_CUE;
        func_00239AD0(0xFFFF);
    }
    func_00239AC0(mode);
    func_00235178(INTC_TIM2);
    if (intr) EIntr();
    return 0;
}
