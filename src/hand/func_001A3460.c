/* func_001A3460 (0x1A3460): LIGHT virtual slot 16 (Project*Transform): after the LO projection, rebuild the light
 * when the XF it hangs off has moved on since the last rebuild. */
#include "light.h"

void func_001A5E80(LIGHT *plight);   /* LO slot 16 */

void func_001A3460(LIGHT *plight)
{
    XF *pxf;
    int nStamp;

    func_001A5E80(plight);
    pxf = plight->alo.pxf;
    nStamp = 0;
    if (pxf != NULL)
        nStamp = pxf->nStamp;
    if (plight->nStampXf < nStamp) {
        plight->nStampXf = nStamp;
        func_001A3968(plight);
    }
}
