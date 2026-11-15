/* class: CID_JOBHOLD2 (0xBC, on a 0x27 object; SafeHouse aijobs.cpp JOBHOLD::Enter, shared with 0xBB, without the
 * frame turn): the base enter, then a JOBMOVE of animation state index 2 (standing). */
#include "vtbl.h"
#include "cid.h"
#include "aijob.h"

/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x3C - 0x10]; int nAnim; };
void Enter__5AIJOB(AIJOB *pjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */

void func_0017D2E0(AIJOB *pjob)
{
    struct JOBVT *pjobMove;
    VTENT *pvte;
    Enter__5AIJOB(pjob);
    pjobMove = func_00205438(pjob->pguard, CID_JOBMOVE);
    pjobMove->nAnim = 2;
    pvte = &pjobMove->vt[8];
    ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte));
}
