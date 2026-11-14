/* class: the hack swarms (SafeHouse hack.cpp, orig 0x00181E10: a hit one alive again after D_002BE884 (0.15) s):
 * repeated while its state changes. */
#include "clock.h"
struct LO;
struct SWQ {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ int state;
    /* 0x28 */ float tState;
};
extern float D_002BE884;   /* 0.15f */
void SetSwarmQState__FP2LOP3SWQi(struct LO *plo, struct SWQ *pswq, int state);

void func_00181E10(struct LO *plo, struct SWQ *pswq)
{
    int state;
    do {
        state = pswq->state;
        if (state == 1 && g_clock.t - pswq->tState > D_002BE884) {
            SetSwarmQState__FP2LOP3SWQi(plo, pswq, 0);
        }
    } while (pswq->state != state);
}
