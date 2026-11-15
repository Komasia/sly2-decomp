/* JOBSURROUND::Update: while following: the path is recomputed (to the guard's place around the target,
 * PosSurroundPlace, in its navigation region) and followed again unless the follow is still fresh (its +0x70 at most
 * D_002BE748) and the path's end is still in the place's zone: within the target's angle (TARGETREC +0x18) of the
 * target's heading and in the guard's distance range (+0x324). */
#include "h2_aijobs.h"

extern float D_002BE748;
struct NAVREGION;
struct NAV { char pad0[0x10]; struct NAVREGION *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
/* the guard's curve: its points */
struct CRV { char pad0[0xE8]; int cpos; char padEC[8]; qword *apos; };
/* the pursued object's record; field: SafeHouse port (aipursuit.h TARGETREC) */
struct TARGETREC { char pad0[0xC]; struct LO *plo; char pad10[8]; float radWide; };
struct GUARD {
    /* 0x000 */ char pad0[0xE8];
    /* 0x0e8 */ struct SOPHYS *pE8;     /* -> +0xDC -> +0x10: the navigation region it is in */
    /* 0x0ec */ char padEC[0x294 - 0xEC];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) */
    /* 0x298 */ char pad298[0x324 - 0x298];
    /* 0x324 */ char lmSurround[0xA8];  /* field: SafeHouse port (g324 / g328) - the distance range around the target */
    /* 0x3cc */ struct TARGETREC *ptarget;   /* field: SafeHouse port (ptarget3CC) */
};
struct JOBFOLLOW { char pad0[0x70]; float g70; };
void Update__5AIJOB(JOBSURROUND *pjob);
float RadTargetrec__FP9TARGETREC(struct TARGETREC *ptarget);
qword PosOfLo__FP2LO(void *plo);
void ConvertVectorToCylind__FG9VU_VECTORPfN21(qword vec, float *prad, float *ps, int pz);
float RadNormalize__Ff(float rad);
int FCheckLm(void *plm, float g) asm("FCheckLm__FP2LMf");
qword PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(JOBSURROUND *pjob, struct NAVREGION *pnavregion, float rad, qword pos);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(struct NAVREGION *pnavregion, qword posFrom, qword posTo, struct CRV *pcrv);
void Follow__9JOBFOLLOWP3CRVi(struct JOBFOLLOW *pjobFollow, struct CRV *pcrv, int n);

// name: SafeHouse port (JOBSURROUND::Update)
void Update__11JOBSURROUND(JOBSURROUND *pjob)
{
    struct GUARD *pguard;
    struct SOPHYS *psophys;
    struct NAV *pnav;
    struct NAVREGION *pnavregion;
    struct CRV *pcrv;
    struct TARGETREC *ptarget;
    void *ploTarget;
    float radTarget;
    struct JOBFOLLOW *pjobFollow;
    float cyl[2];
    qword posTarget;
    Update__5AIJOB(pjob);
    pnav = 0;
    if (pjob->st != SURS_Stand) {
        pguard = pjob->aijob.pguard;
        psophys = pguard->pE8;
        pcrv = pguard->pcrv;
        if (psophys) pnav = psophys->pnav;
        pnavregion = pnav ? pnav->pnavregion : 0;
        ptarget = pguard->ptarget;
        ploTarget = ptarget->plo;
        radTarget = RadTargetrec__FP9TARGETREC(ptarget);
        posTarget = PosOfLo__FP2LO(ploTarget);
        pjobFollow = (struct JOBFOLLOW *)pjob->aijob.pchild;
        if (pjobFollow->g70 > D_002BE748) goto repath;
        {
            /* the path's end, from the target */
            qword dv;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(dv) : "j"(pcrv->apos[pcrv->cpos - 1]), "j"(posTarget));
            ConvertVectorToCylind__FG9VU_VECTORPfN21(dv, &cyl[0], &cyl[1], 0);
        }
        if (__builtin_fabsf(RadNormalize__Ff(cyl[0] - radTarget)) > ptarget->radWide) goto repath;
        if (FCheckLm(pjob->aijob.pguard->lmSurround, cyl[1])) return;
repath:
        {
            qword pos = PosOfLo__FP2LO(pjob->aijob.pguard);
            FNavPathCrv__FP9NAVREGIONiiP3CRV(pnavregion, pos, PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(pjob, pnavregion, radTarget, posTarget), pcrv);
        }
        Follow__9JOBFOLLOWP3CRVi(pjobFollow, pcrv, 0);
    }
}
