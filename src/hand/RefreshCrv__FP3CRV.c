/* RefreshCrv: forget a curve's search caches (the last segment found and the cached segment's sub-lengths). */
#include "crv.h"

// name: SafeHouse port (RefreshCrv)
void RefreshCrv__FP3CRV(CRV *pcrv)
{
    pcrv->iseg = 0;
    pcrv->isegCached = -1;
}
