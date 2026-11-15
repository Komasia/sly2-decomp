/* SFromCrvG: the distance along a curve at parameter g: in its segment, linear in the parameter for a linear curve,
 * else from the cached segment's sub-lengths (CacheSegCrv) at the parameter's tenth. Layout: crv.h CRV.
 * g is not named: it arrives in $f12 and goes on untouched to ISegCrvG (whose g is its float argument). */
#include "crv.h"

int ISegCrvG__FP3CRVPfT1f(CRV *pcrv, float *pdg, float *pdgSeg);
void CacheSegCrv__FP3CRVi(CRV *pcrv, int iseg);
static __inline__ float GLerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
// name: SafeHouse port (SFromCrvG)
float SFromCrvG__FP3CRV(CRV *pcrv)
{
    float dg, dgSeg;
    float s;
    int iseg = ISegCrvG__FP3CRVPfT1f(pcrv, &dg, &dgSeg);
    if (pcrv->crvk == CRVK_Linear) {
        s = GLerp(pcrv->as[iseg], pcrv->as[iseg + 1], dg / dgSeg);
    } else {
        float u;
        int isub;
        CacheSegCrv__FP3CRVi(pcrv, iseg);
        u = dg * 10.0f / dgSeg;
        isub = (int)u;
        s = GLerp(pcrv->asSub[isub], pcrv->asSub[isub + 1], u - isub);
        s += pcrv->as[iseg];
    }
    return s;
}
