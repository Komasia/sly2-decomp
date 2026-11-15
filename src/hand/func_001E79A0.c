/* func_001E79A0: rope option 1044's getter (EOPID 1210): the rope's length, its last point's rest distance
 * (0 for a path without points) (SafeHouse rope.cpp). Layout: crv.h CRV, h3_rope.h ROPE. */
#include "h3_rope.h"

ROPE *PropeEnsure__FP2LOi(CRV *ppath, int f);
float func_001E79A0(CRV *ppath)
{
    float s;
    if (ppath->cpoint > 0) s = PropeEnsure__FP2LOi(ppath, 0)->as5C[ppath->cpoint - 1];
    else s = 0.0f;
    return s;
}
