/* func_001E5D80: Init (virtual slot 6) of PATH (CID_PATH, derived from XFM): the XFM Init, then the curve's search
 * caches: no cached segment, last segment found 1 (SafeHouse crv.cpp). Layout: crv.h CRV. */
#include "crv.h"

struct XFM;
void InitXfm__FP3XFM(struct XFM *pxfm);

void func_001E5D80(CRV *pcrv)
{
    InitXfm__FP3XFM((struct XFM *)pcrv);
    pcrv->isegCached = -1;
    pcrv->iseg = 1;
}
