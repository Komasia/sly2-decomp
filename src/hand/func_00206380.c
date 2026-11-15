#include "stepguard.h"
#include "vtbl.h"
/* the other object (an ALO): vtable, attachment */
struct ALOV { char pad[0xC]; VTENT *pvt; char pad2[0xEC - 0x10]; void *poxa; };
struct ALOX { char pad[0xEC]; void *poxa; };
/* the guard's carry job (cid 0xB1) */
struct JOBB1 { char pad[0x50]; int nState; char pad2[8]; struct ALOX *paloTarget; };
int OverlapKindAlo__FP3ALOT0(struct GUARD *pguard, struct ALOV *paloOther);
int FGuardState(struct GUARD *pguard, int st) asm("FGuardState__FP5GUARDi");
struct JOBB1 *PjobFind__FP5GUARDPv(void *pbhvstk, int cid);
int func_00134310(int okResult, int grf);   /* ORs an overlap kind bit */
/* OverlapKindGuard (0x206380): GUARD's overlap kind with another object: the ALO's, plus kind bit 1 while the guard
 * is in state 7 against an object whose vt slot 62 says no, or in state 0x17 (carrying, job 0xB1 in states 0 / 4 / 5)
 * against the object it carries. */
// name: SafeHouse port (OverlapKindGuard)
int OverlapKindGuard__FP3ALOT0(struct GUARD *pguard, struct ALOV *paloOther)
{
    int okResult = OverlapKindAlo__FP3ALOT0(pguard, paloOther);
    if (FGuardState(pguard, 7)) {
        if (!((int (*)(void *))paloOther->pvt[62].pfn)(VT_THIS(paloOther, &paloOther->pvt[62])))
            okResult = func_00134310(okResult, 1);
    } else if (FGuardState(pguard, 0x17)) {
        struct JOBB1 *pjob = PjobFind__FP5GUARDPv(pguard->step.bhvstk, 0xB1);
        if (paloOther->poxa == pjob->paloTarget->poxa) {
            switch (pjob->nState) {
            case 0:
            case 4:
            case 5:
                okResult = func_00134310(okResult, 1);
                break;
            }
        }
    }
    return okResult;
}
