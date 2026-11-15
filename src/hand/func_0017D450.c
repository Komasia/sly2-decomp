/* JOBGOTO::SetState: the child job ends (kept between the path states), then the new state's child: arrived: a
 * JOBSTAND facing the object; crossing a link: a JOBLINK; on a path: the JOBFOLLOW (new or reused) set on the
 * guard's curve; to the fallback point: a JOBNAVPOINT. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

/* a pushed child job, as seen through its vtable: JOBSTAND (+0x38 ploFace), JOBLINK (+0x30 plink), JOBNAVPOINT
 * (+0x30 goal), JOBFOLLOW (+0x40 fNoAvoid, +0xC0 the walk's guard state, +0xC8 the object followed) */
struct JOBVT {
    char pad0[0xC]; VTENT *vt; char pad10[0x20];
    union { NAVLINK *plink; qword q; struct { int pad[2]; struct LO *ploFace; } stand; } u30;
    union { int fNoAvoid; qword q; } u40;
    char pad50[0xC0 - 0x50]; int nAnim; int padC4; struct LO *plo;
};
/* the guard's fields used here */
struct GUARD {
    /* 0x000 */ char pad0[0x294];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) - the curve its paths are written to */
    /* 0x298 */ char pad298[0xFE8 - 0x298];
    /* 0xfe8 */ int grfFE8;             /* field: SafeHouse port */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
void Follow__9JOBFOLLOWP3CRVi(struct JOBVT *pjobFollow, struct CRV *pcrv, int n);

// name: SafeHouse port (JOBGOTO::SetState)
void SetState__7JOBGOTOi(JOBGOTO *pjob, int st)
{
    if (st == pjob->st) return;
    if (!((unsigned)st < 3 && pjob->st >= 0 && pjob->st < 3)) EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case GOTOS_Arrived:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte; pjobStand->u30.stand.ploFace = pjob->plo; pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        break;
    case GOTOS_Link:
        { struct JOBVT *pjobLink = func_00205438(pjob->aijob.pguard, CID_JOBLINK); VTENT *pvte; pjobLink->u30.plink = pjob->aplink[0]; pvte = &pjobLink->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobLink, pvte)); }
        break;
    case GOTOS_Path:
    case GOTOS_PathOpen:
        {
            struct JOBVT *pjobFollow = (struct JOBVT *)pjob->aijob.pchild;
            if (pjobFollow == 0) {
                VTENT *pvte;
                pjobFollow = func_00205438(pjob->aijob.pguard, CID_JOBFOLLOW);
                pjobFollow->plo = pjob->plo;
                pjobFollow->u40.fNoAvoid = pjob->fDirect;
                if (!pjob->plo || pjob->fAC || !(pjob->aijob.pguard->grfFE8 & 4)) pjobFollow->nAnim = 9; else pjobFollow->nAnim = 8;
                Follow__9JOBFOLLOWP3CRVi(pjobFollow, pjob->aijob.pguard->pcrv, 0);
                pvte = &pjobFollow->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobFollow, pvte));
            } else {
                Follow__9JOBFOLLOWP3CRVi(pjobFollow, pjob->aijob.pguard->pcrv, 0);
            }
        }
        break;
    case GOTOS_None:
    case GOTOS_Search:
        break;
    case GOTOS_Point:
        { struct JOBVT *pjobPoint = func_00205438(pjob->aijob.pguard, CID_JOBNAVPOINT); VTENT *pvte; pjobPoint->u30.q = ((qword *)&pjob->goalFallback)[0]; pjobPoint->u40.q = ((qword *)&pjob->goalFallback)[1]; pvte = &pjobPoint->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobPoint, pvte)); }
        break;
    }
}
