/* JOBLADDER::SetLadderState: the child job ends; at the goal (1): a JOBMOVE of animation state index 2 and the speed
 * cleared; climbing (0): a JOBMOVE of index 9. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x3C - 0x10]; int nAnim; };
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */

// name: SafeHouse port (JOBLADDER::SetLadderState)
void SetLadderState__9JOBLADDERi(JOBLADDER *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case 1:
        { struct JOBVT *pjobMove = func_00205438(pjob->aijob.pguard, CID_JOBMOVE); VTENT *pvte; pjobMove->nAnim = 2; pvte = &pjobMove->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte)); } pjob->gSpeed = 0.0f;
        break;
    case 0:
        { struct JOBVT *pjobMove = func_00205438(pjob->aijob.pguard, CID_JOBMOVE); VTENT *pvte; pjobMove->nAnim = 9; pvte = &pjobMove->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte)); }
        break;
    }
}
