/* func_001E7410: the point of a curve minimizing pfn(g, pv) over its points' parameters (SafeHouse jumptgt.cpp: the
 * best score's knot); its point / direction (EvalCrv), parameter and distance. pposBest / pdirBest are declared
 * int here: EvalCrv's g (its float argument) goes last so the call keeps the original argument order. */
#include "crv.h"

extern float D_002A813C;    /* FLT_MAX */
void EvalCrv__FP3CRVfP6VECTORT2(CRV *pcrv, int pposBest, int pdirBest, float g);
float SFromCrvG__FP3CRV(CRV *pcrv, float g);
void func_001E7410(CRV *pcrv, float (*pfn)(float, void *), void *pv, int pposBest, int pdirBest, float *pg, float *ps)
{
    int i;
    float gBest = 0.0f;
    float rMin = D_002A813C;
    for (i = 0; i < pcrv->cpoint; i++) {
        float g = pcrv->ag[i];
        float r = pfn(g, pv);
        if (r < rMin) {
            rMin = r;
            gBest = g;
        }
    }
    if (pposBest || pdirBest) EvalCrv__FP3CRVfP6VECTORT2(pcrv, pposBest, pdirBest, gBest);
    if (pg) *pg = gBest;
    if (ps) *ps = SFromCrvG__FP3CRV(pcrv, gBest);
}
