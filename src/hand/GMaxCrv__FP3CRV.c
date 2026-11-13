/* GMaxCrv: the parameter of a curve's last point. */
#include "crv.h"

// name: SafeHouse port (GMaxCrv)
float GMaxCrv__FP3CRV(CRV *pcrv)
{
    return pcrv->ag[pcrv->cpoint - 1];
}
