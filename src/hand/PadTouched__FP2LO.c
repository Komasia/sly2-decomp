/* PadTouched (a pad's deferred touch call): an actor that touched it in its jump state 0x11, or that just bounced
 * off (jump kind 3 within 0.15 s), is ignored (the toucher forgotten); otherwise the pad goes to state 1 (0x1490A0).
 * Layout: SafeHouse port (pad.cpp PAD, actor.h JUMP at +0x2C0). */
#include "clock.h"

struct ACTOR {
    /* 0x000 */ char pad0[0x2c4];
    /* 0x2c4 */ int kindJump;           /* SafeHouse: jump.kind */
    /* 0x2c8 */ char pad2C8[0x2dc - 0x2c8];
    /* 0x2dc */ int stJump;             /* SafeHouse: jump.state */
    /* 0x2e0 */ float tJump;            /* SafeHouse: jump.t20, its start */
};
struct PAD {
    /* 0x000 */ char pad0[0x2f8];
    /* 0x2f8 */ struct ACTOR *ploFound; /* field: SafeHouse port - the toucher */
};
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void func_001490A0(struct PAD *ppad, int state);   /* SafeHouse: SetPadState */

// name: SafeHouse port (PadTouched)
void PadTouched__FP2LO(struct PAD *ppad)
{
    if (FIsBasicDerivedFrom__FP5BASIC3CID(ppad->ploFound, 0x34)) {
        struct ACTOR *pactor = ppad->ploFound;
        if (pactor->stJump == 0x11 || (pactor->kindJump == 3 && g_clock.t - pactor->tJump < 0.15f)) {
            ppad->ploFound = 0;
            return;
        }
    }
    func_001490A0(ppad, 1);
}
