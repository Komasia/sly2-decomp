/* JOBHOLD::Enter (0xBB, hanging on a bar): the base enter, a JOBMOVE of animation state index 2 (standing), and the
 * guard's heading frame (+0x1B0) turned to the bar's x row (a look-at frame with z up). */
#include "vtbl.h"
#include "cid.h"
#include "aijob.h"

typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { qword a, b, c; };
/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x3C - 0x10]; int nAnim; };
struct GUARD {
    /* 0x000 */ char pad0[0x1B0];
    /* 0x1b0 */ struct MATRIX3 matHeading;   /* field: SafeHouse port (STEP +0x1B0: the heading's frame) */
    /* 0x1e0 */ char pad1E0[0xF84 - 0x1E0];
    /* 0xf84 */ void *ploMove;               /* field: SafeHouse port - the bar */
};
extern qword g_normalZ;
void Enter__5AIJOB(AIJOB *pjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
qword *MatJtLo__FP2LO(void *plo);
struct MATRIX3 BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(qword vecLook, qword vecUp);

// name: SafeHouse port (JOBHOLD::Enter)
void Enter__7JOBHOLD(AIJOB *pjob)
{
    struct JOBVT *pjobMove; VTENT *pvte; struct GUARD *pguard;
    Enter__5AIJOB(pjob);
    pjobMove = func_00205438(pjob->pguard, CID_JOBMOVE); pjobMove->nAnim = 2; pvte = &pjobMove->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobMove, pvte));
    pguard = pjob->pguard;
    pguard->matHeading = BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(*MatJtLo__FP2LO(pguard->ploMove), g_normalZ);
}
