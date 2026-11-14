/* class: REACH (the actor's reach at +0x900; SafeHouse jtthrow.cpp OverlapKindActor: "the reach's 0x1CC9A8: in
 * state 1, the target's attachment: 3"): the overlap kind with another object - at least 3 while reaching (state 1)
 * for an object attached (OXA +0xEC) where the target (or its parent) is. */
typedef struct OXA OXA;
typedef struct ALO {
    /* 0x00 */ char pad0[0xec];
    /* 0xec */ OXA *poxa;
} ALO;
typedef struct REACH {
    /* 0x00 */ char pad0[0x84];
    /* 0x84 */ void *ploTarget;   /* field: SafeHouse port */
    /* 0x88 */ char pad88[0x1c];
    /* 0xa4 */ int state;         /* field: SafeHouse port */
} REACH;

ALO *PaloOrParent__FPv(void *plo);
int func_00134310(int kind, int kindOther);   /* the larger overlap kind */

int func_001CC9A8(REACH *preach, ALO *paloOther, int kind)
{
    if (preach->state == 1) {
        ALO *palo = PaloOrParent__FPv(preach->ploTarget);
        if (palo != 0 && palo->poxa != 0 && paloOther->poxa == palo->poxa) {
            kind = func_00134310(kind, 3);
        }
    }
    return kind;
}
