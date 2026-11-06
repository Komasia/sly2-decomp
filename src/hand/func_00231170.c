/* LoadXfmFromBrx (0x231170): XFM virtual slot 13: read the XFM's own data (func_00231768), then the LO data
 * (LoadOptionsFromBrx__FPvP18CBinaryInputStream). */
#include "so.h"

void func_00231768(XFM *pxfm, void *pbis);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(XFM *pxfm, void *pbis);

void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(XFM *pxfm, void *pbis)
{
    func_00231768(pxfm, pbis);
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(pxfm, pbis);
}
