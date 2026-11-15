/* OverlapKindHide (the hiding spots' vt slot 61): the ALO's overlap kind, but no contacts (at least 1, 0x134310)
 * with an actor (cid 0x34) hiding in it (interaction kind 1 on it) or jumping into / out of it (its jump states 6 / 7
 * with it). Layout: SafeHouse port (actor.h: inter at +0x4C0, jump at +0x2C0). */
#include "cid.h"
#include "actor.h"
struct ALO;
int OverlapKindAlo__FP3ALOT0(struct ALO *palo, struct ACTOR *pactor);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_00134310(int kind, int kindMin);   /* the larger overlap kind */

// name: SafeHouse port (OverlapKindHide)
int OverlapKindHide__FP3ALOT0(struct ALO *palo, struct ACTOR *pactor)
{
    int kind = OverlapKindAlo__FP3ALOT0(palo, pactor);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pactor, CID_ACTOR)) {
        if (pactor->inter.kind == 1 && palo == pactor->inter.ploTarget)
            kind = func_00134310(kind, 1);
        if ((unsigned int)(pactor->jump.state - 6) < 2 && palo == pactor->jump.ploC)
            kind = func_00134310(kind, 1);
    }
    return kind;
}
