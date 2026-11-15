/* JOBSHOOT::SetShootState: the child job ends, leaving the shot clears the guard's shooting flag; the shot plays the
 * guard's state 0x11 (a JOBMOVE child facing the target) and sets the flag. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x38 - 0x10]; struct LO *ploFace; int nAnim; };
struct GUARD {
    /* 0x000 */ char pad0[0xF60];
    /* 0xf60 */ int fShooting;          /* field: SafeHouse port (fF60) */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */

// name: SafeHouse port (JOBSHOOT::SetShootState)
void SetShootState__8JOBSHOOTi(JOBSHOOT *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    if (!pjob->st) pjob->aijob.pguard->fShooting = 0;
    pjob->st = st;
    pjob->tSt = g_clock.t;
    if (!st) {
        struct JOBVT *pjobMove = func_00205438(pjob->aijob.pguard, CID_JOBMOVE);
        VTENT *pvte;
        pjobMove->nAnim = 0x11;
        pjobMove->ploFace = pjob->ptarget;
        pvte = &pjobMove->vt[8];
        ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte));
        pjob->aijob.pguard->fShooting = 1;
    }
}
