/* SetGuardPursued: the object a guard pursues (+0x38C) and the target record it joins (+0x3CC): it leaves the old
 * one's record and joins the new one's. Layout: SafeHouse port (guard.h GUARD). */
struct LO;
struct TARGETREC;
struct GUARD {
    /* 0x000 */ char pad0[0x38c];
    /* 0x38c */ struct LO *ploPursued;          /* field: SafeHouse port */
    /* 0x390 */ char pad390[0x3cc - 0x390];
    /* 0x3cc */ struct TARGETREC *ptarget3CC;   /* field: SafeHouse port */
};
void RemoveTargetrecGuard__FP9TARGETREC(struct TARGETREC *ptrec, struct GUARD *pguard);
struct TARGETREC *PtargetrecOf__FP2LO(struct LO *plo);
void AddTargetrecGuard__FP9TARGETRECP5GUARD(struct TARGETREC *ptrec, struct GUARD *pguard);

// name: SafeHouse port (SetGuardPursued)
void SetGuardPursued__FP5GUARDP2LO(struct GUARD *pguard, struct LO *plo)
{
    struct LO *ploOld = pguard->ploPursued;
    if (plo != ploOld) {
        if (ploOld != 0) {
            RemoveTargetrecGuard__FP9TARGETREC(pguard->ptarget3CC, pguard);
            pguard->ptarget3CC = 0;
        }
        pguard->ploPursued = plo;
        if (plo != 0) {
            struct TARGETREC *ptrec = PtargetrecOf__FP2LO(plo);
            pguard->ptarget3CC = ptrec;
            AddTargetrecGuard__FP9TARGETRECP5GUARD(ptrec, pguard);
        }
    }
}
