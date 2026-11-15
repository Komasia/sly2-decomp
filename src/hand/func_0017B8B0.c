/* JOBB2::SetB2State: the child job ends; standing: a JOBSTAND, the guard pursued by nobody; pursuing: a JOBPURSUE of
 * the selected object (+0x40 set); held: a JOBSTAND of kind 1. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable (JOBSTAND: +0x3C nAnim; JOBPURSUE: +0x30 the target, +0x40) */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x30 - 0x10]; struct LO *ptarget; char pad34[0x3C - 0x34]; int nAnim; int n40; };
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
void SetGuardPursued__FP5GUARDP2LO(struct GUARD *pguard, struct LO *plo);

// name: SafeHouse port (JOBB2::SetB2State)
void SetB2State__5JOBB2i(JOBB2 *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case B2S_Stand:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        SetGuardPursued__FP5GUARDP2LO(pjob->aijob.pguard, 0);
        break;
    case B2S_Pursue:
        { struct JOBVT *pjobPursue = func_00205438(pjob->aijob.pguard, CID_JOBPURSUE); VTENT *pvte; pjobPursue->ptarget = pjob->ploSelected; pjobPursue->n40 = 1; pvte = &pjobPursue->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobPursue, pvte)); }
        break;
    case B2S_Held:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte; pjobStand->nAnim = 1; pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        break;
    }
}
