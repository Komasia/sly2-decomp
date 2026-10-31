/* LoadXfmFromBrx (0x231170): XFM virtual slot 13: read the XFM's own data (func_00231768), then the LO data
 * (func_0013F810). */
#include "so.h"

void func_00231768(XFM *pxfm, void *pbis);
void func_0013F810(XFM *pxfm, void *pbis);

void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(XFM *pxfm, void *pbis)
{
    func_00231768(pxfm, pbis);
    func_0013F810(pxfm, pbis);
}
