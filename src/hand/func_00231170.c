/* LoadXfmFromBrx (0x231170): XFM virtual slot 13: read the XFM's own data (LoadLoxBaseFromBrx), then the LO data
 * (LoadOptionsFromBrx__FPvP18CBinaryInputStream). */
#include "so.h"

void LoadLoxBaseFromBrx(XFM *pxfm, void *pbis);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(XFM *pxfm, void *pbis);

void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(XFM *pxfm, void *pbis)
{
    LoadLoxBaseFromBrx(pxfm, pbis);
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(pxfm, pbis);
}
