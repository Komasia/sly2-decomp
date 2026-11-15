/* func_001E7B38: the distance from sFrom to sTo along a curve; on a closed curve the shorter way round
 * (SafeHouse aijobs.cpp). Layout: crv.h CRV. */
#include "crv.h"

float SMaxCrv__FP3CRV(CRV *pcrv);
float func_001E7B38(CRV *pcrv, float sFrom, float sTo)
{
    float ds = sTo - sFrom;
    if (pcrv->fClosed) {
        float sLength = SMaxCrv__FP3CRV(pcrv);
        if (ds > sLength * 0.5f) ds -= sLength;
        else if (ds < sLength * -0.5f) ds += sLength;
    }
    return ds;
}
