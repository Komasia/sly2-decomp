/* ISegCrvS: the segment of a curve containing distance s (wrapped), searched from the last one found (iseg); also
 * s's offset into it and its length. Layout: crv.h CRV. */
#include "crv.h"

float SWrapCrv__FP3CRVf(CRV *pcrv, float s);

static inline int Before(int a, int b)
{
    register int result __asm__("$2");
    __asm__("slt %0,%1,%2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}

static inline int LoopEnd(int value)
{
    register int result __asm__("$5");
    __asm__("daddu %0,%1,$zero" : "=r"(result) : "r"(value));
    return result;
}

static inline int Cpoint(CRV *pcrv)
{
    register int value __asm__("$3");
    __asm__("lw %0,%1" : "=r"(value) : "m"(pcrv->cpoint));
    return value;
}

// name: SafeHouse port (ISegCrvS)
int ISegCrvS__FP3CRVPfT1f(CRV *pcrv, float *pds, float *pdsSeg, float s)
{
    int iseg;
    s = SWrapCrv__FP3CRVf(pcrv, s);
    iseg = pcrv->iseg;
    if (pcrv->as[iseg] < s) {
        int isegLast = Cpoint(pcrv) - 1;
        if (!Before(iseg, isegLast)) goto forwardDone;
        if (s < pcrv->as[iseg]) goto forwardDone;
        {
            int isegEnd = LoopEnd(isegLast);
            do {
                ++iseg;
                if (iseg >= isegEnd) break;
                if (s < pcrv->as[iseg]) break;
            } while (1);
        }
forwardDone:
        --iseg;
    } else {
        for (; iseg > 0; iseg--)
            if (pcrv->as[iseg] <= s) break;
    }
    if (pds) *pds = s - pcrv->as[iseg];
    if (pdsSeg) *pdsSeg = pcrv->as[iseg + 1] - pcrv->as[iseg];
    pcrv->iseg = iseg;
    return iseg;
}
