/* DgStepCrv: a search step along a curve: its parameter span over ten times its point count. Layout: crv.h CRV. */
#include "crv.h"

float GMaxCrv__FP3CRV(CRV *pcrv);
float GMinCrv__FP3CRV(CRV *pcrv);
// name: SafeHouse port (DgStepCrv)
float DgStepCrv__FP3CRV(CRV *pcrv)
{
    float gMax = GMaxCrv__FP3CRV(pcrv);
    return (gMax - GMinCrv__FP3CRV(pcrv)) / (pcrv->cpoint * 10.0f);
}
