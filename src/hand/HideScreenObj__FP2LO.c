/* HideScreenObj (the screen objects' vt slot 50): its timer set to 1, and without a hide part (+0x78 -1) it stops
 * (state 1). Source: SafeHouse port (screenrt.h). */
struct LO {
    /* 0x00 */ char pad0[0x78];
    /* 0x78 */ int idHide;   /* the hide part (-1 none) */
};
void SetTimerTimers__FP5TIMER6TIMERS(struct LO *plo, int timers);
void SetState__FP8SCREENRTi(struct LO *plo, int state);

// name: SafeHouse port (HideScreenObj, screenrt.h)
void HideScreenObj__FP2LO(struct LO *plo)
{
    SetTimerTimers__FP5TIMER6TIMERS(plo, 1);
    if (plo->idHide == -1)
        SetState__FP8SCREENRTi(plo, 1);
}
