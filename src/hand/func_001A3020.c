/* The subtitle box (SafeHouse soundglue.cpp: screen object 0x373, found by the HUD's 0x1A3020 at each world start),
 * its timers on. */
struct LO;
struct SW;
extern struct SW g_sw;
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);
void SetTimerTimers__FP5TIMER6TIMERS(struct LO *ptimer, int timers);

void func_001A3020(struct LO **pploSubtitle)
{
    struct LO *plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, 0x373, 0);
    *pploSubtitle = plo;
    if (plo != 0) {
        SetTimerTimers__FP5TIMER6TIMERS(plo, 1);
    }
}
