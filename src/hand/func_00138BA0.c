/* TRKGBL::Eval: a blended scalar channel at t: the blend's phase (t over its length, or the segment of the blended
 * table and the fraction into it), then each weighted BL's track evaluated at the same phase of its own clip (or of
 * the same segment of its own table) with its rate scaled to match, summed by weight; BLs without the channel give g.
 * Layout: SafeHouse port (blend.h TRKGBL). */
#include "vtbl.h"
struct MRSG { float t; float dt; };   /* field: SafeHouse port (blend.h) */
struct AMRSGT { int ibAmrsg; int cmrsg; struct MRSG *amrsg; };   /* a segment table */
struct ASEGBL { char pad[0x74]; float tMax; char pad2[0xC0 - 0x78]; int cbBl; int cbl; char *abl; };   /* field: SafeHouse port (blend.h ASEGBL) */
struct BLENDBL { float weight; struct ASEGBL *paseg; };   /* field: SafeHouse port */
struct V;
struct V { VTENT *vt; };   /* a BL's scalar track (TRKG: vt slot 2 Eval) */
struct TRKGBL { int x0; struct ASEGBL *pbl; struct AMRSGT *pamrsgt; struct V **atrk; float g; };   /* field: SafeHouse port (blend.h TRKGBL) */

extern int ImrsgLookUp(int, int, float, float, float *) asm("ImrsgLookUp__FffiP4MRSGPf");

// name: SafeHouse port (TRKGBL::Eval)
void Eval__6TRKGBLPfT1ff(struct TRKGBL *ptrk, float t, float dtScale, float *pg, float *pdg)
{
    float dtIn;
    float g4;
    float g8;
    float uPhase;
    float gSum, dgSum;
    struct MRSG *pmrsg;
    struct ASEGBL *pbl;
    int i;
    int imrsg;

    if (ptrk->pamrsgt == 0) {
        uPhase = t / ptrk->pbl->tMax;
    } else {
        imrsg = ImrsgLookUp(ptrk->pamrsgt->cmrsg, (int)ptrk->pamrsgt->amrsg, t, ptrk->pbl->tMax, &dtIn);
        pmrsg = &ptrk->pamrsgt->amrsg[imrsg];
        uPhase = dtIn / pmrsg->dt;
    }
    dgSum = 0.0f;
    gSum = dgSum;
    for (i = 0; i < ptrk->pbl->cbl; i++) {
        struct BLENDBL *pblT = (struct BLENDBL *)(ptrk->pbl->abl + i * ptrk->pbl->cbBl);
        struct V *ptrkBl;
        if (pblT->weight == 0.0f)
            continue;
        ptrkBl = ptrk->atrk[i];
        if (ptrkBl == 0) {
            g8 = 0;
            g4 = ptrk->g;
        } else {
            float u, s;
            if (ptrk->pamrsgt == 0) {
                float lim = pblT->paseg->tMax;
                s = dtScale * lim / ptrk->pbl->tMax;
                u = uPhase * lim;
            } else {
                struct MRSG *pmrsgBl = &((struct MRSG *)((char *)pblT + ptrk->pamrsgt->ibAmrsg))[imrsg];
                float lim = pblT->paseg->tMax;
                u = pmrsgBl->t + uPhase * pmrsgBl->dt;
                s = dtScale * pmrsgBl->dt / pmrsg->dt;
                if (lim < u)
                    u -= lim;
            }
            ((void (*)(void *, float, float, float *, float *))ptrkBl->vt[2].pfn)(VT_THIS(ptrkBl, &ptrkBl->vt[2]), u, s, &g4, &g8);
        }
        gSum += pblT->weight * g4;
        dgSum += pblT->weight * g8;
    }
    if (pg)
        *pg = gSum;
    if (pdg)
        *pdg = dgSum;
}
