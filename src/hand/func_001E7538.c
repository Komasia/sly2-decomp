/* ISegCrvG: the segment of a curve containing parameter g (wrapped), searched from the last one found (iseg);
 * also g's offset into it and its parameter span. Layout: crv.h CRV. */
#include "crv.h"

float GWrapCrv__FP3CRVf(CRV *pcrv, float g);
// name: SafeHouse port (ISegCrvG)
int ISegCrvG__FP3CRVPfT1f(CRV *pcrv, float *pdg, float *pdgSeg, float g)
{
    int iseg;
    g = GWrapCrv__FP3CRVf(pcrv, g);
    iseg = pcrv->iseg;
    if (pcrv->ag[iseg] < g) {
        int isegLast = pcrv->cpoint - 1;
        while (iseg < isegLast) {
            if (g < pcrv->ag[iseg]) break;
            iseg++;
        }
        iseg--;
    } else {
        while (iseg > 0) {
            if (pcrv->ag[iseg] <= g) break;
            iseg--;
        }
    }
    {
        float g0 = pcrv->ag[iseg];
        if (pdg) *pdg = g - g0;
        if (pdgSeg) *pdgSeg = pcrv->ag[iseg + 1] - g0;
    }
    pcrv->iseg = iseg;
    return iseg;
}
