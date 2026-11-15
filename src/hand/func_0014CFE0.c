#include "clock.h"

unsigned long func_0014D240(struct CLOCK *p);
void ResetClock__FP5CLOCK(struct CLOCK *p);
void func_0014CFE0(void)
{
    unsigned long c[2];
    unsigned int i;
    float *pf;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(c[0]));
    g_clock.tickLastRaw = c[0];
    g_clock.tickFrame = func_0014D240(&g_clock);
    for (i = 0; i < 9; i++) g_clock.art[i] = 1.0f;
    g_clock.rt = 1.0f;
    g_clock.rtCm = 1.0f;
    ResetClock__FP5CLOCK(&g_clock);
}
