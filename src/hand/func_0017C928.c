/* JOBSTATION::SetState: the child job ends; hurrying: a JOBGOTO (move 0x1C) after the object itself; held: a
 * JOBSTAND facing it (kind 1); going: a JOBGOTO to the station point (moved out of the object's frame). The object's
 * position is remembered (posLast) for the goal updates. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a goal (SafeHouse aijobs.h GOAL): a path, an object, or a fixed point */
/* a pushed child job, as seen through its vtable (JOBSTAND +0x38 / +0x3C; JOBGOTO +0x38 nAnim, +0xA8 / +0xAC, +0xC0) */
struct JOBVT {
    char pad0[0xC]; VTENT *vt; char pad10[0x38 - 0x10]; int n38; int n3C; char pad40[0xA8 - 0x40];
    struct LO *ploA8; int nAC; char padB0[0x10]; int nC0;
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
qword PosOfLo__FP2LO(struct LO *plo);
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct LO *ploFrom, int ploTo, qword pos);
void func_002562A8(struct GOAL *pgoal);   /* the goal cleared */
void SetGoal__7JOBGOTOP4GOAL(struct JOBVT *pjobGoto, struct GOAL *pgoal);

// name: SafeHouse port (JOBSTATION::SetState)
void SetState__10JOBSTATIONi(JOBSTATION *pjob, int st)
{
    struct GOAL goal;
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case STATS_Hurrying:
        {
            struct JOBVT *pjobGoto = func_00205438(pjob->aijob.pguard, CID_JOBGOTO);
            qword pos = PosOfLo__FP2LO(pjob->plo);
            VTENT *pvte;
            pjob->posLast = pos;
            pjobGoto->nC0 = 1; pjobGoto->ploA8 = pjob->plo; pjobGoto->nAC = 1;
            func_002562A8(&goal);
            goal.pos = pos;
            SetGoal__7JOBGOTOP4GOAL(pjobGoto, &goal);
            pjobGoto->n38 = 0x1C;
            pvte = &pjobGoto->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobGoto, pvte));
        }
        break;
    case STATS_Held:
        {
            struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND);
            VTENT *pvte;
            pjobStand->n38 = (int)pjob->plo;
            pjobStand->n3C = 1;
            pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte));
        }
        break;
    case STATS_Going:
        {
            struct JOBVT *pjobGoto = func_00205438(pjob->aijob.pguard, CID_JOBGOTO);
            qword pos;
            VTENT *pvte;
            pjob->posLast = PosOfLo__FP2LO(pjob->plo);
            pos = ConvertPos__FP2LOT0G9VU_VECTOR(pjob->plo, 0, pjob->pos);
            pjobGoto->nC0 = 1;
            func_002562A8(&goal);
            goal.pos = pos;
            SetGoal__7JOBGOTOP4GOAL(pjobGoto, &goal);
            pjobGoto->ploA8 = pjob->plo;
            pvte = &pjobGoto->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobGoto, pvte));
        }
        break;
    }
}
