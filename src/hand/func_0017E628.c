/* JOBLINK (SafeHouse aijobs.cpp 0x17E628): a jumped record: a JOBUSE (extra 1) to the record's point. */
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* the pushed JOBUSE, as seen through its vtable (pos 0x50, nExtra 0x68) */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x40]; qword pos; char pad60[8]; int nExtra; };
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
qword PosOfLo__FP2LO(struct GUARD *pguard);
qword PosGoal__FP4GOALG9VU_VECTOR(GOAL *pgoal, qword posFrom);

void func_0017E628(JOBLINK *pjob)
{
    struct JOBVT *pjobUse = func_00205438(pjob->aijob.pguard, CID_JOBUSE);
    VTENT *pvte;
    pjobUse->nExtra = 1;
    pjobUse->pos = PosGoal__FP4GOALG9VU_VECTOR(&pjob->plink->agoal[pjob->irec], PosOfLo__FP2LO(pjob->aijob.pguard));
    pvte = &pjobUse->vt[8];
    ((void (*)(void *))pvte->pfn)(VT_THIS(pjobUse, pvte));
}
