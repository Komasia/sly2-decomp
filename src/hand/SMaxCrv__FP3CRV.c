/* SMaxCrv: the distance of a curve's last point, i.e. its length (SafeHouse: SLengthCrv 0x1E6648). */
#include "crv.h"

// name: SafeHouse port (SMaxCrv)
float SMaxCrv__FP3CRV(CRV *pcrv)
{
    return pcrv->as[pcrv->cpoint - 1];
}
