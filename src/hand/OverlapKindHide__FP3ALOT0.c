/* OverlapKindHide (the hiding spots' vt slot 61): the ALO's overlap kind, but no contacts (at least 1, 0x134310)
 * with an actor (cid 0x34) hiding in it (interaction kind 1 on it) or jumping into / out of it (its jump states 6 / 7
 * with it). Layout: SafeHouse port (actor.h: inter at +0x4C0, jump at +0x2C0). */
struct ALO;
struct ACTOR {
    /* 0x000 */ char pad0[0x2cc];
    /* 0x2cc */ struct ALO *ploJump;       /* SafeHouse: jump.ploC */
    /* 0x2d0 */ char pad2D0[0x2dc - 0x2d0];
    /* 0x2dc */ int stJump;                /* SafeHouse: jump.state */
    /* 0x2e0 */ char pad2E0[0x4c8 - 0x2e0];
    /* 0x4c8 */ int n4C8;                  /* field: SafeHouse port - the interaction kind */
    /* 0x4cc */ char pad4CC[0x4d4 - 0x4cc];
    /* 0x4d4 */ struct ALO *ploInteract;   /* SafeHouse: inter.ploTarget */
};
int OverlapKindAlo__FP3ALOT0(struct ALO *palo, struct ACTOR *pactor);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_00134310(int kind, int kindMin);   /* the larger overlap kind */

// name: SafeHouse port (OverlapKindHide)
int OverlapKindHide__FP3ALOT0(struct ALO *palo, struct ACTOR *pactor)
{
    int kind = OverlapKindAlo__FP3ALOT0(palo, pactor);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pactor, 0x34)) {
        if (pactor->n4C8 == 1 && palo == pactor->ploInteract)
            kind = func_00134310(kind, 1);
        if ((unsigned int)(pactor->stJump - 6) < 2 && palo == pactor->ploJump)
            kind = func_00134310(kind, 1);
    }
    return kind;
}
