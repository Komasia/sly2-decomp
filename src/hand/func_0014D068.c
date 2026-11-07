struct CLK { char pad[0x18]; float af[9]; };
extern struct CLK g_clock;
void UpdateClockRate__FP5CLOCK(void *p);
// name: SafeHouse port (ResetClock)
void ResetClock__FP5CLOCK(int *p)
{
    *p = 0;
    g_clock.af[0] = 1.0f;
    g_clock.af[1] = 1.0f;
    g_clock.af[2] = 1.0f;
    g_clock.af[5] = 1.0f;
    g_clock.af[6] = 1.0f;
    g_clock.af[8] = 1.0f;
    g_clock.af[7] = 1.0f;
    g_clock.af[4] = 1.0f;
    UpdateClockRate__FP5CLOCK(p);
}
