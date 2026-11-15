/* JOBBD::SetState: the child job ends; alerted: a JOBMOVE (index 0xB) facing the object; away: a JOBGOTO (move 0x1C,
 * an inexact path will do) to the point chosen away from it; held: a JOBSTAND (kind 1). */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable: JOBMOVE / JOBSTAND (+0x38 ploFace, +0x3C nAnim), JOBGOTO (+0x38
 * nAnim, +0xC0 fInexact) */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x28];
    union { struct LO *ploFace; int nAnim; } u38; int n3C; char pad40[0xC0 - 0x40]; int nC0; };
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
void ChooseAway__5JOBBD(JOBBD *pjob);

// name: SafeHouse port (JOBBD::SetState)
void SetState__5JOBBDi(JOBBD *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case BDS_Alerted:
        { struct JOBVT *pjobMove = func_00205438(pjob->aijob.pguard, CID_JOBMOVE); VTENT *pvte; pjobMove->n3C = 0xB; pjobMove->u38.ploFace = pjob->ploFrom; pvte = &pjobMove->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte)); }
        break;
    case BDS_Away:
        { struct JOBVT *pjobGoto = func_00205438(pjob->aijob.pguard, CID_JOBGOTO); VTENT *pvte; pjobGoto->nC0 = 1; pjobGoto->u38.nAnim = 0x1C; ChooseAway__5JOBBD(pjob); pvte = &pjobGoto->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobGoto, pvte)); }
        break;
    case BDS_Held:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte; pjobStand->n3C = 1; pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        break;
    }
}
