/* func_001E6DB8: NearestCrv's search on a cubic curve: the parameter minimizing the (constrained) distance to pos
 * (MinimizeRange over func_001E69A0, from g in steps of a tenth of the first segment, over the whole real line on
 * a closed curve, else between the end parameters), wrapped; then the point / direction, parameter and distance.
 * SafeHouse: part of NearestCrv. */
#include "crv.h"

struct CNSTR;
struct NEARCTX { CRV *pcrv; struct CNSTR *pcnstr; int pad[2]; qword pos; };
extern float D_002A8130;    /* -FLT_MAX */
extern float D_002A8134;    /* FLT_MAX */
float func_001E69A0(void *pv, float g);
void MinimizeRange(float (*pfn)(void *, float), void *pv, float g, float dg, float gMin, float gMax, float *pg, float *pgOut) asm("MinimizeRange__FPFPvf_fPvffffPfT6");
float GWrapCrv__FP3CRVf(CRV *pcrv, float g);
void EvalCrv__FP3CRVfP6VECTORT2(CRV *pcrv, float g, qword *ppos, qword *pdir);
float SFromCrvG__FP3CRV(CRV *pcrv, float g);
void func_001E6DB8(CRV *pcrv, qword pos, struct CNSTR *pcnstr, qword *pposNearest, qword *pdir, float *pg, float *ps, float g)
{
    struct NEARCTX ctx;
    float gNearest;
    ctx.pcnstr = pcnstr; ctx.pos = pos; ctx.pcrv = pcrv;
    MinimizeRange(func_001E69A0, &ctx, g, (pcrv->ag[1] - pcrv->ag[0]) * 0.1f,
                  pcrv->fClosed ? D_002A8130 : pcrv->ag[0],
                  pcrv->fClosed ? D_002A8134 : pcrv->ag[pcrv->cpoint - 1], &gNearest, 0);
    gNearest = GWrapCrv__FP3CRVf(pcrv, gNearest);
    if (pposNearest || pdir) EvalCrv__FP3CRVfP6VECTORT2(pcrv, gNearest, pposNearest, pdir);
    if (pg) *pg = gNearest;
    if (ps) *ps = SFromCrvG__FP3CRV(pcrv, gNearest);
}
