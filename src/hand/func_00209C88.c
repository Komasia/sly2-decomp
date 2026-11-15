#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct GUARD;
struct GUARD { char pad[0xC]; VTENT *pvt; char pad2[0x218 - 0x10]; qword *pposProbe0; char pad3[0xF80 - 0x21C]; int kMove; void *ploMove; float sMove; int pad4; void *ploHands; };
extern qword D_002A2DA0;   /* a fixed direction */
void func_001F4FA8(struct GUARD *pguard);   /* the base slot (nothing) */
void EvalCrvS(void *pcrv, qword *ppos, qword *pdir, float s) asm("EvalCrvS__FP3CRVfP6VECTORT2");
qword PosOfLo__FP2LO(void *plo);
qword *MatJtLo__FP2LO(void *plo);

/* AddGuardRailContacts (0x209C88): the guard's line contacts (vt slot 82, as AddActorLineXps) holding it on what it
 * moves on (kMove: 0 a rail, 1 a pipe, 2 a cid 0x13 object, 3 a cid 0x27 object): along the object's curve at
 * sMove (its floor probe or its hands' point), or at the object's position along its x row / a fixed direction (D_002A2DA0). */
// name: SafeHouse port (AddGuardRailContacts)
void AddGuardRailContacts__FP3ALO(struct GUARD *pguard)
{
    qword posRail, dirRail;
    func_001F4FA8(pguard);
    switch (pguard->kMove) {
    case 0:
        EvalCrvS(pguard->ploMove, &posRail, &dirRail, pguard->sMove);
        ((void (*)(void *, int, void *, qword, qword, qword))pguard->pvt[82].pfn)(VT_THIS(pguard, &pguard->pvt[82]), 0x22, pguard->ploMove, posRail, dirRail, *pguard->pposProbe0);
        break;
    case 1: {
        VTENT *pvte;
        void *pthis;
        EvalCrvS(pguard->ploMove, &posRail, &dirRail, pguard->sMove);
        pvte = &pguard->pvt[82];
        pthis = VT_THIS(pguard, pvte);
        ((void (*)(void *, int, void *, qword, qword, qword))pvte->pfn)(pthis, 7, pguard->ploMove, posRail, dirRail, PosOfLo__FP2LO(pguard->ploHands));
        break;
    }
    case 2: {
        VTENT *pvte = &pguard->pvt[82];
        void *pthis = VT_THIS(pguard, pvte);
        ((void (*)(void *, int, void *, qword, qword, qword))pvte->pfn)(pthis, 7, pguard->ploMove, PosOfLo__FP2LO(pguard->ploMove), *MatJtLo__FP2LO(pguard->ploMove), PosOfLo__FP2LO(pguard->ploHands));
        break;
    }
    case 3: {
        VTENT *pvte = &pguard->pvt[82];
        void *pthis = VT_THIS(pguard, pvte);
        ((void (*)(void *, int, void *, qword, qword, qword))pvte->pfn)(pthis, 7, pguard->ploMove, PosOfLo__FP2LO(pguard->ploMove), D_002A2DA0, *pguard->pposProbe0);
        break;
    }
    }
}
