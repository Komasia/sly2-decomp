/* GFromCrvS: the parameter of a curve at distance s: in its segment, linear in the distance for a linear curve,
 * else found among the cached segment's sub-lengths (CacheSegCrv), one tenth of the segment's parameter span each.
 * Layout: crv.h CRV. */
#include "crv.h"

int ISegCrvS__FP3CRVPfT1f(CRV *pcrv, float *pds, float *pdsSeg, float s);
void CacheSegCrv__FP3CRVi(CRV *pcrv, int iseg);

static __inline__ float GLerp(float a, float b, float t)
{
    return (1.0f - t) * a + t * b;
}

static inline float ReturnValue(float value)
{
    register float input __asm__("$f4") = value;
    float result;
    __asm__("mov.s %0,%1" : "=f"(result) : "f"(input));
    return result;
}

// name: SafeHouse port (GFromCrvS)
float GFromCrvS__FP3CRVf(CRV *pcrv, float s)
{
    float ds, dsSeg;
    float g;
    int iseg = ISegCrvS__FP3CRVPfT1f(pcrv, &ds, &dsSeg, s);

    if (pcrv->crvk == CRVK_Linear) {
        {
            float fraction = ds / dsSeg;
            float gUpper = *(volatile float *)&pcrv->ag[iseg + 1];
            float gLower = *(volatile float *)&pcrv->ag[iseg];
            g = GLerp(gLower, gUpper, fraction);
        }
    } else {
        int isub;
        CacheSegCrv__FP3CRVi(pcrv, iseg);
        for (isub = 1; isub < CSUB_CRV - 1; isub++)
            if (ds < pcrv->asSub[isub]) break;
        isub--;
        {
            float part = (ds - pcrv->asSub[isub]) / (pcrv->asSub[isub + 1] - pcrv->asSub[isub]);
            float fsub = isub;
            part = (fsub + part) * 0.1f;
            g = GLerp(pcrv->ag[iseg], pcrv->ag[iseg + 1], part);
        }
    }
    return ReturnValue(g);
}
