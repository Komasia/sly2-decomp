/* GWrapCrv: a parameter of a closed curve wrapped into [first, last point's parameter]; an open curve's unchanged.
 * Layout: crv.h CRV. */
#include "crv.h"

float GModPositive__Fff(float g, float gMax);
// name: SafeHouse port (GWrapCrv)
float GWrapCrv__FP3CRVf(CRV *pcrv, float g)
{
    float gMin, gMax;
    if (!pcrv->fClosed) return g;
    gMin = pcrv->ag[0];
    gMax = pcrv->ag[pcrv->cpoint - 1];
    if (gMin <= g && g <= gMax) return g;
    return gMin + GModPositive__Fff(g - gMin, gMax - gMin);
}
