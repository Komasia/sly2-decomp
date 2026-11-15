/* JOBSURROUND::SetSurroundState: the child job ends; standing: a JOBSTAND facing the pursued target; following: a
 * JOBFOLLOW along the guard's curve (+0x294), kind 8, toward the target. */
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable (JOBSTAND: +0x38 the object faced; JOBFOLLOW: +0xC0, +0xC8) */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x38 - 0x10]; struct LO *ploFace; char pad3C[0xC0 - 0x3C]; int nC0; int padC4; struct LO *ploC8; };
struct CRV;
struct TARGETREC { char pad0[0xC]; struct LO *plo; };   /* field: SafeHouse port (aipursuit.h) - the target */
struct GUARD {
    /* 0x000 */ char pad0[0x294];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) */
    /* 0x298 */ char pad298[0x3CC - 0x298];
    /* 0x3cc */ struct TARGETREC *ptarget;   /* field: SafeHouse port (ptarget3CC) - the pursued object's record */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
void Follow__9JOBFOLLOWP3CRVi(struct JOBVT *pjobFollow, struct CRV *pcrv, int n);

// name: SafeHouse port (JOBSURROUND::SetSurroundState)
void SetSurroundState__11JOBSURROUNDi(JOBSURROUND *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    switch (st) {
    case SURS_Stand:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte; pjobStand->ploFace = pjob->aijob.pguard->ptarget->plo; pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        break;
    case SURS_Follow:
        { struct JOBVT *pjobFollow = func_00205438(pjob->aijob.pguard, CID_JOBFOLLOW); VTENT *pvte; Follow__9JOBFOLLOWP3CRVi(pjobFollow, pjob->aijob.pguard->pcrv, 0); pjobFollow->nC0 = 8; pjobFollow->ploC8 = pjob->aijob.pguard->ptarget->plo; pvte = &pjobFollow->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobFollow, pvte)); }
        break;
    }
}
