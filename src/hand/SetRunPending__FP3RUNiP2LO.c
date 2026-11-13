/* SetRunPending: a script run's pending command and the object working on it; the old and the new object are told
 * (0x143DE8: their link back to the run, +0x1084). Source: SafeHouse port (scpt.cpp). */
struct LO;
struct RUN {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int icPending;       /* field: SafeHouse port */
    /* 0x44 */ struct LO *ploWatch; /* field: SafeHouse port */
};
void func_00143DE8(struct LO *plo, struct RUN *prun);   /* the actor's script run */

// name: SafeHouse port (SetRunPending)
void SetRunPending__FP3RUNiP2LO(struct RUN *prun, int ic, struct LO *plo)
{
    struct LO *ploOld;
    if (ic != prun->icPending)
        prun->icPending = ic;
    ploOld = prun->ploWatch;
    if (plo != ploOld) {
        if (ploOld != 0)
            func_00143DE8(ploOld, 0);
        prun->ploWatch = plo;
        if (plo != 0)
            func_00143DE8(plo, prun);
    }
}
