// UpdatePathrec: when an AI region under a path changed (its stamp +0x114 past the record's), sample the path over
// [sStart, sEnd] every D_002C367C (50) and collect the spans inside the polygons met along it (PpolyAtPoint; the
// span's ends from NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff, 3 meaning "the path doesn't leave it", so the path's
// ends are used), join them with the loaded spans (CMergeAlsg__FiP3LSGiT1iT1i), fix up a pair across the seam of a
// closed path, and take a new stamp. SafeHouse spawner.cpp. Layout: h3_rope.h PATHREC, crv.h CRV.
// Notes for whoever touches this again:
//  - `pspanFix` (the aspan pointer used by the seam fix-up) must be assigned after the copy loops, outside the block
//    that uses it, so cse does not fold pspanFix[0] into 0x10(ppathrec); gcse then keeps it as a separate spilled copy.
//  - `nIter` is a dead iteration counter. It only adds a few insns before gcse, which resizes gcse's expression hash
//    table (101 -> 103 buckets) and so renumbers the PRE reaching registers; that decides the order of the two spill
//    slots (0xC1C/0xC20) for &alsgLoaded[0] and the aspan copy. Without it the two slots are swapped.
#include "h3_rope.h"

struct VEC { float x, y, z, w; } __attribute__((aligned(16)));
struct NAVREGION { char pad[0x114]; int nStamp; };
/* a span as CMergeAlsg sees it (an LSG, 0x60 bytes: only its two parameters are used) */
struct LSGSPAN { char pad[0x40]; float sMin; float sMax; char pad2[0x18]; } __attribute__((aligned(16)));
struct SW_ { char pad[0x3D70]; int nNavStamp; };
extern struct SW_ g_sw;
extern float D_002C367C;    /* the sampling step, 50 */
float SMinCrv__FP3CRV(CRV *pcrv);
float SMaxCrv__FP3CRV(CRV *pcrv);
void EvalCrvS(CRV *pcrv, float s, qword *ppos, qword *pdir) asm("EvalCrvS__FP3CRVfP6VECTORT2");
void *PpolyAtPoint__FG9VU_VECTOR(qword pos);
int NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(void *ppoly, CRV *pcrv, float s, int fForward, qword *ppos, float *ps);
void *s1_memset(void *, int, unsigned int) asm("memset");
int CMergeAlsg__FiP3LSGiT1iT1i(int, struct LSGSPAN *, int, struct LSGSPAN *, int, struct LSGSPAN *, int);

// name: SafeHouse port (UpdatePathrec)
void UpdatePathrec__FP7PATHREC(PATHREC *ppathrec)
{
    struct VEC pos;
    struct LSGSPAN alsgLoaded[16];
    struct LSGSPAN alsg[16];
    float sSpanStart, sSpanEnd;
    PATHSPAN *aspan;
    PATHSPAN *aspanLoaded;
    int cspan, cspanLoaded, i, j, k, n, nIter = 0;
    PATHSPAN *pspanFix;
    float sStart, s, sEnd;
    {
        int k;
        for (k = 0; k < ppathrec->cpreg; k++)
            if (ppathrec->nStamp < ppathrec->apreg[k]->nStamp)
                break;
        if (k >= ppathrec->cpreg)
            return;
    }
    aspan = ppathrec->aspan;
    cspan = 0;
    sStart = SMinCrv__FP3CRV(ppathrec->ppath);
    s = sStart;
    sEnd = SMaxCrv__FP3CRV(ppathrec->ppath);
    aspanLoaded = ppathrec->aspanLoaded;
    cspanLoaded = ppathrec->cspanLoaded;
    while (s < sEnd) {
        void *ppoly;
        EvalCrvS(ppathrec->ppath, s, (qword *)&pos, 0);
        ppoly = PpolyAtPoint__FG9VU_VECTOR(*(qword *)&pos);
        if (ppoly) {
            int fClosedSave = ppathrec->ppath->fClosed;
            PATHSPAN *pspan;
            int fNew;
            int ispan;
            ppathrec->ppath->fClosed = 0;
            if (NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(ppoly, ppathrec->ppath, s, 0, 0, &sSpanStart) == 3)
                sSpanStart = sStart;
            if (NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(ppoly, ppathrec->ppath, s, 1, 0, &sSpanEnd) == 3)
                sSpanEnd = sEnd;
            ppathrec->ppath->fClosed = fClosedSave;
            /* the spans it overlaps replaced; one beginning before it extended */
            pspan = &aspan[cspan];
            fNew = 1;
            while (aspan < pspan) {
                PATHSPAN *pspanPrev = pspan - 1;
                if (pspanPrev->sMax < sSpanStart)
                    break;
                pspan = pspanPrev;
                if (pspan->sMin < sSpanStart) {
                    fNew = 0;
                    break;
                }
            }
            ispan = pspan - aspan;
            cspan = ispan + 1;
            if (!((unsigned)cspan < CSPAN_PATHREC + 1))
                cspan = ispan;
            if (fNew)
                pspan->sMin = sSpanStart;
            pspan->sMax = sSpanEnd;
            s = sSpanEnd;
        }
        nIter++;
        s += D_002C367C;
    }
    for (i = 0; i < cspanLoaded; i++) {
        s1_memset(&alsgLoaded[i], 0, 0x60);
        alsgLoaded[i].sMin = aspanLoaded[i].sMin;
        alsgLoaded[i].sMax = aspanLoaded[i].sMax;
    }
    for (j = 0; j < cspan; j++) {
        s1_memset(&alsg[j], 0, 0x60);
        alsg[j].sMin = aspan[j].sMin;
        alsg[j].sMax = aspan[j].sMax;
    }
    pspanFix = ppathrec->aspan;
    n = CMergeAlsg__FiP3LSGiT1iT1i(cspan, alsg, cspanLoaded, alsgLoaded, CSPAN_PATHREC, alsg, 0);
    for (k = 0; k < n; k++) {
        aspan[k].sMin = alsg[k].sMin;
        aspan[k].sMax = alsg[k].sMax;
    }
    if (n >= 2 && ppathrec->ppath->fClosed) {
        // across the seam: the first span starts at sStart and the last ends at sEnd, so shift them across it
        if (pspanFix[0].sMin == sStart && pspanFix[n - 1].sMax == sEnd) {
            pspanFix[0].sMin = pspanFix[n - 1].sMin - sEnd;
            pspanFix[n - 1].sMax = pspanFix[0].sMax + sEnd;
        }
    }
    ppathrec->cspan = n;
    ppathrec->nStamp = ++g_sw.nNavStamp;
}
