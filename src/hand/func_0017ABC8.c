/* JOBB1::UpdateTarget: while tracking, the owner's launch target for the time left (its vt slot 96); gone: tracking
 * stops; else the launch's target controller gets the new goal, moved into the guard's position frame. */
#include "clock.h"
#include "vtbl.h"
#include "h2_aijobs.h"

struct LOVT { char pad0[0xC]; VTENT *vt; };
/* the owner's launch target; field: SafeHouse port (aijobs.h LAUNCHTARGET) */
struct LAUNCHTARGET { int fActive; float sRadius; float dz; int pad; float pos[4]; float vel[4]; };   /* (4-aligned here, as the matched frame) */
struct CTRLTARGET { char pad0[0x1C]; float tArrive; };   /* field: SafeHouse port */
struct XF { char pad0[0xA0]; int pxfRef; };
struct GUARD {
    /* 0x000 */ char pad0[0x58];
    /* 0x058 */ struct XF *pxfPos;      /* the position's transform */
};
void GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(JOBB1 *pjob, struct LAUNCHTARGET *ptarget, qword *ppos, qword *pvel);
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int pxfFrom, int pxfTo, qword pos);
qword VecConvertXfs__FP2XFT0G9VU_VECTOR(int pxfFrom, int pxfTo, qword vec);
void SetGoal__10CTRLTARGETG9VU_VECTORT1(struct CTRLTARGET *pctrl, qword pos, qword vel);

// name: SafeHouse port (JOBB1::UpdateTarget)
void UpdateTarget__5JOBB1(JOBB1 *pjob)
{
    struct LAUNCHTARGET target;
    qword pos, vel;
    struct XF *pxf;
    qword posLocal;
    if (!pjob->fTrack) return;
    { struct LOVT *plo = (struct LOVT *)pjob->ploOwner; VTENT *pvte = &plo->vt[0x60]; ((void (*)(void *, struct LAUNCHTARGET *, float))pvte->pfn)(VT_THIS(plo, pvte), &target, pjob->pctrlTarget->tArrive - g_clock.t); }
    if (!target.fActive) { pjob->fTrack = 0; return; }
    pxf = pjob->jobmove.aijob.pguard->pxfPos;
    GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(pjob, &target, &pos, &vel);
    posLocal = PosConvertXfs__FP2XFT0G9VU_VECTOR(0, pxf->pxfRef, pos);
    SetGoal__10CTRLTARGETG9VU_VECTORT1(pjob->pctrlTarget, posLocal, VecConvertXfs__FP2XFT0G9VU_VECTOR(0, pxf->pxfRef, vel));
}
