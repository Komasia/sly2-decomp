/* FDamageFatal (actor vt slot 86): whether a hit is fatal - it takes at least the actor's damage capacity and is not
 * a touch (kinds 0 / 1), kind 0x80000 or healing (0x100000). */
/* only diff: original assembler padded a backward branch (to a jr) with a nop at 0x14443C; asfix.py does not pad when a jump is in between. Code otherwise identical. */
#include "actor.h"

/* the contact message of a hit (SafeHouse so.h CTMSG) */
struct CTMSG {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ int grfFilter;   /* field: SafeHouse port - the hit's kind */
    /* 0x10 */ int nState;      /* field: SafeHouse port - the damage (negative) */
};

#define DMGK_Touch0  0
#define DMGK_Touch1  1
#define DMGK_80000   0x80000
#define DMGK_Heal    0x100000

// name: SafeHouse port (FDamageFatal)
int FDamageFatal__FP5ACTORP5CTMSG(struct ACTOR *pactor, struct CTMSG *pctm)
{
    if (-pctm->nState < pactor->cHealthMax) return 0;
    switch (pctm->grfFilter) {
    case DMGK_Touch0:
    case DMGK_Touch1:
    case DMGK_80000:
    case DMGK_Heal:
        return 0;
    }
    return 1;
}
