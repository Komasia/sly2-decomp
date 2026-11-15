/* SWrapCrv: a distance along a closed curve wrapped into [0, its length]; an open curve's unchanged.
 * Layout: crv.h CRV. */
#include "crv.h"

float GModPositive__Fff(float g, float gMax);
// name: SafeHouse port (SWrapCrv)
float SWrapCrv__FP3CRVf(CRV *pcrv, float s)
{
    float sMax;
    if (!pcrv->fClosed) return s;
    sMax = pcrv->as[pcrv->cpoint - 1];
    if (0.0f <= s && s <= sMax) return s;
    return GModPositive__Fff(s, sMax);
}
