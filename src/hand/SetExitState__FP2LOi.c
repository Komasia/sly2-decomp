/* SetExitState (the exits, class 0x1A, that start an episode): a new state and its time; state 4 keeps the exit
 * updating through its delay (0x1A6CA8), pauses the game (3: the pad locked) and makes it the world's pending exit
 * (+0x3C84). Layout: SafeHouse port (lo.h nState / tState, sw.h ploExitPending). */
#include "clock.h"

struct LO {
    /* 0x000 */ char pad0[0x13c];
    /* 0x13c */ int nState;    /* field: SafeHouse port */
    /* 0x140 */ float tState;  /* field: SafeHouse port */
};
struct SW {
    /* 0x0000 */ char pad0[0x3c84];
    /* 0x3c84 */ struct LO *ploExitPending;   /* field: SafeHouse port */
};
extern struct SW g_sw;
void func_001A6CA8(struct LO *plo, int fActive);
void PauseGame__FP9GAMEPAUSEi(struct SW *psw, int n);

// name: SafeHouse port (SetExitState)
void SetExitState__FP2LOi(struct LO *plo, int n)
{
    if (n != plo->nState) {
        if (n == 4) {
            func_001A6CA8(plo, 1);
            PauseGame__FP9GAMEPAUSEi(&g_sw, 3);
            g_sw.ploExitPending = plo;
        }
        plo->nState = n;
        plo->tState = g_clock.t;
    }
}
