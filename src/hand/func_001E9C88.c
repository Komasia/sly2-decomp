/* func_001E9C88: build a path's AI record: sample the path from its start to its end every D_002C367C (50),
 * collect the distinct AI regions under the samples (PregionAt__FG9VU_VECTORi) into apreg[64] and the spans
 * where the path is off the regions (no region, a different region than the sample before, or off its triangles:
 * func_001C0920) into aspan[64] (joining the first and last span across the seam of a closed path), then copy
 * both lists to the heap (PvAllocSwCopyImpl__FiPv); the spans in use start as the loaded ones, stamp -1.
 * SafeHouse spawner.cpp (Pathrec). Layout: h3_rope.h PATHREC, crv.h CRV.
 * Matching note: the &apreg argument of the final PvAllocSwCopyImpl__FiPv call must go through an inline helper;
 * integrate.c then puts sp+0x200 straight into a1, so gcse has nothing to hoist and the apreg[cpreg++] cursor (s6)
 * keeps an un-noted init in the loop preheader. The ALLOC request reuses pos2's stack slot. */
#include "h3_rope.h"

struct ALLOC { int cb; int cbAlign; };
extern float D_002C367C;    /* the sampling step, 50 */
float SMinCrv__FP3CRV(CRV *pcrv);
float SMaxCrv__FP3CRV(CRV *pcrv);
void EvalCrvS(CRV *pcrv, float s, qword *ppos, qword *pdir) asm("EvalCrvS__FP3CRVfP6VECTORT2");
void *PregionAt__FG9VU_VECTORi(qword pos, int f);
int func_001C0920(void *preg, qword pos, int n);
void *PvAllocSwCopyImpl__FiPv(struct ALLOC *palloc, void *pv);
void CopyAb(void *, const void *, unsigned) asm("CopyAb__FPvT0Ui");
static inline void *PvReallocMsg(struct ALLOC *palloc, int cb, int cbAlign, void *pv) { palloc->cb = cb; palloc->cbAlign = cbAlign; return PvAllocSwCopyImpl__FiPv(palloc, pv); }
void func_001E9C88(PATHREC *ppathrec, CRV *ppath)
{
    PATHSPAN aspan[64];
    void *apreg[CREG_PATHREC_MAX];
    qword pos;
    qword pos2;
    PATHSPAN *pspan = 0;
    int cpreg = 0;
    int cspan = 0;
    float sStart, sPrev, s, sEnd;
    void *pregPrev;

    ppathrec->ppath = ppath;
    sStart = SMinCrv__FP3CRV(ppath);
    sPrev = sStart;
    s = sStart;
    sEnd = SMaxCrv__FP3CRV(ppathrec->ppath);
    EvalCrvS(ppathrec->ppath, sStart, &pos, 0);
    pregPrev = PregionAt__FG9VU_VECTORi(pos, 0);
    for (; s < sEnd; s += D_002C367C) {
        void *preg;
        int fOff;
        EvalCrvS(ppathrec->ppath, s, &pos2, 0);
        preg = PregionAt__FG9VU_VECTORi(pos2, 0);
        if (preg) {
            int i;
            for (i = 0; i < cpreg; i++)
                if (apreg[i] == preg)
                    break;
            if (i >= cpreg && (unsigned)cpreg < CREG_PATHREC_MAX)
                apreg[cpreg++] = preg;
        }
        fOff = 0;
        if (!preg || pregPrev != preg || !func_001C0920(pregPrev, pos2, 0))
            fOff = 1;
        if (fOff) {
            if (!pspan && cspan < 64) {
                pspan = &aspan[cspan++];
                pspan->sMin = sPrev;
            }
        } else if (pspan) {
            pspan->sMax = s;
            pspan = 0;
        }
        sPrev = s;
        pregPrev = preg;
    }
    if (pspan)
        pspan->sMax = sEnd;
    if (cspan >= 2 && ppathrec->ppath->fClosed && aspan[0].sMin == sStart && aspan[cspan - 1].sMax == sEnd) {
        aspan[0].sMin = aspan[cspan - 1].sMin - sEnd;
        aspan[cspan - 1].sMax = aspan[0].sMax + sEnd;
    }
    ppathrec->cspanLoaded = cspan;
    ppathrec->aspanLoaded = PvReallocMsg((struct ALLOC *)&pos2, cspan * 8, 0x10, aspan);
    ppathrec->cspan = cspan;
    CopyAb(ppathrec->aspan, aspan, cspan * 8);
    ppathrec->cpreg = cpreg;
    ppathrec->apreg = PvReallocMsg((struct ALLOC *)&pos2, cpreg * 4, 0x10, apreg);
    ppathrec->nStamp = -1;
}
