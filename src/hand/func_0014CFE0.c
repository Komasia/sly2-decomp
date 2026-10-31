struct CLOCK {
    float t;
    float dt;
    float rDt;
    float rDtPrev;
    char pad[8];
    float af[9];
    char pad2[0x48 - 0x3C];
    unsigned long tick;
    unsigned long tickLast;
    int hi;
};
extern struct CLOCK g_clock;
unsigned long func_0014D240(struct CLOCK *p);
void func_0014D068(struct CLOCK *p);
void func_0014CFE0(void)
{
    unsigned long c[2];
    unsigned int i;
    float *pf;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(c[0]));
    g_clock.tickLast = c[0];
    g_clock.tick = func_0014D240(&g_clock);
    for (i = 0; i < 9; i++) g_clock.af[i] = 1.0f;
    g_clock.rDt = 1.0f;
    g_clock.rDtPrev = 1.0f;
    func_0014D068(&g_clock);
}
