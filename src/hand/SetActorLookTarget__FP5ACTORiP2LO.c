/* SetActorLookTarget: the actor's look target (its kind and object); a new object while the look timer runs
 * (+0x114C not FLT_MAX) turns the look on (+0x1148) and clears +0x1100 (0x142860). Layout: SafeHouse port (actor.h). */
struct LO;
struct ACTOR {
    /* 0x0000 */ char pad0[0x10f8];
    /* 0x10f8 */ struct LO *ploLook;   /* field: SafeHouse port - the object looked at */
    /* 0x10fc */ int nLookKind;        /* field: SafeHouse port */
    /* 0x1100 */ char pad1100[0x1148 - 0x1100];
    /* 0x1148 */ int fLook;            /* field: SafeHouse port */
    /* 0x114c */ float tLookNext;      /* field: SafeHouse port */
};
extern float D_002A4D60;   /* FLT_MAX */
void func_00142860(struct ACTOR *pactor);

// name: SafeHouse port (SetActorLookTarget)
void SetActorLookTarget__FP5ACTORiP2LO(struct ACTOR *pactor, int nKind, struct LO *plo)
{
    if (plo != pactor->ploLook || nKind != pactor->nLookKind) {
        pactor->nLookKind = nKind;
        pactor->ploLook = plo;
        if (plo != 0) {
            if (pactor->tLookNext != D_002A4D60) {
                pactor->fLook = 1;
                func_00142860(pactor);
            }
        }
    }
}
