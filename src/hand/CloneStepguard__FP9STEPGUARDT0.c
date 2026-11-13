/* CloneStepguard: a step guard cloned from another: the base clone (0x203A08), the current move reference (+0xFD0)
 * set up for this guard (0x209770); the guard keeps its own detector (+0xF64), which is cloned from the source's
 * detector (its virtual at vt slot 41); then 0x208250. Layout: SafeHouse port (guard.h GUARD). */
#include "vtbl.h"

struct DETECTOR {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
struct STEPGUARD {
    /* 0x000 */ char pad0[0xf64];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port - its detector */
    /* 0xf68 */ char padF68[0xfd0 - 0xf68];
    /* 0xfd0 */ char move[0x10];         /* field: SafeHouse port - the current move (MOVEREF) */
};
void func_00203A08(struct STEPGUARD *pguard, struct STEPGUARD *pguardBase);
void func_00209770(void *pmove, struct STEPGUARD *pguard);
void func_00208250(struct STEPGUARD *pguard);

void CloneStepguard__FP9STEPGUARDT0(struct STEPGUARD *pguard, struct STEPGUARD *pguardBase)
{
    struct DETECTOR *pdet = pguard->pdet;
    VTENT *pvte;
    func_00203A08(pguard, pguardBase);
    func_00209770(pguard->move, pguard);
    pguard->pdet = pdet;
    pvte = &pdet->pvt[0x148 / 8];
    ((void (*)(void *, struct DETECTOR *))pvte->pfn)(VT_THIS(pdet, pvte), pguardBase->pdet);
    func_00208250(pguard);
}
