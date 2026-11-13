/* class: CID_3F, a step guard kind (vt slot 5 = HandleMessage; SafeHouse guard.cpp HandleGuardMessage: a strike
 * (message 0xB) on the guard itself makes the striker seen by its detector, state 1). */
struct DETECTOR;
struct LO;
struct GUARD3F {
    /* 0x000 */ char pad0[0xf64];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port - its detector */
};
struct STRIKEMSG {
    /* 0x0 */ struct GUARD3F *pguard;    /* the object struck */
    /* 0x4 */ struct LO *ploStriker;
};
void HandleStepguardMessage__FP9STEPGUARD5MSGIDPv(struct GUARD3F *pguard, int msgid, void *pv);
int FGuardState__FP5GUARDi(struct GUARD3F *pguard, int state);
void func_00154038(struct DETECTOR *pdet, struct LO *plo, int state);   /* SafeHouse: a target's detector state */

void func_0014B218(struct GUARD3F *pguard, int msgid, struct STRIKEMSG *pmsg)
{
    HandleStepguardMessage__FP9STEPGUARD5MSGIDPv(pguard, msgid, pmsg);
    if (FGuardState__FP5GUARDi(pguard, 0x24) == 0 && msgid == 0xB && pmsg->pguard == pguard) {
        func_00154038(pmsg->pguard->pdet, pmsg->ploStriker, 1);
    }
}
