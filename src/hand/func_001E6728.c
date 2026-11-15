/* SClampCrv: a distance along a curve kept on it: wrapped on a closed curve, else clamped to [start, end].
 * Layout: crv.h CRV. */
#include "crv.h"

float SMinCrv__FP3CRV(CRV *pcrv);
float SMaxCrv__FP3CRV(CRV *pcrv);
float SWrapCrv__FP3CRVf(CRV *pcrv, float s);
static __inline__ float GClamp(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (g > gMax) return gMax; return g; }
// name: SafeHouse port (SClampCrv)
float SClampCrv__FP3CRVf(CRV *pcrv, float s)
{
    if (pcrv->fClosed) return SWrapCrv__FP3CRVf(pcrv, s);
    return GClamp(s, SMinCrv__FP3CRV(pcrv), SMaxCrv__FP3CRV(pcrv));
}
