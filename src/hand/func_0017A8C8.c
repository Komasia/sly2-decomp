/* JOBB0::SetState: the child job ends; each held state plays its move (JOBMOVE child, animation state index 18 grabbed,
 * 19 carried, 20 let go, 21 thrown, 19 extracted) and the guard is busy (+0x32C) while grabbed or carried; no state:
 * the job lets go of the guard. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x3C - 0x10]; int nAnim; };
struct GUARD {
    /* 0x000 */ char pad0[0x32C];
    /* 0x32c */ int fBusy;              /* field: SafeHouse port (f32C: busy) */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
void UnlockJob__FP5AIJOB(JOBB0 *pjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */

// name: SafeHouse port (JOBB0::SetState)
void SetState__5JOBB0i(JOBB0 *pjob, int st)
{
    if (pjob->stHeld == st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->stHeld = st;
    pjob->tHeld = g_clock.t;
    switch (st) {
    case HELDS_Grabbed: case HELDS_Carried: case HELDS_LetGo: case HELDS_Thrown: case HELDS_Extracted:
        {
            struct JOBVT *pjobMove = func_00205438(pjob->aijob.pguard, CID_JOBMOVE);
            int anAnim[5] = { 18, 19, 20, 21, 19 };
            VTENT *pvte;
            pjobMove->nAnim = anAnim[pjob->stHeld];
            pvte = &pjobMove->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte));
        }
        pjob->aijob.pguard->fBusy = (unsigned)pjob->stHeld < 2;
        break;
    case HELDS_None:
        UnlockJob__FP5AIJOB(pjob);
        pjob->aijob.pguard->fBusy = 0;
        break;
    }
}
