/* func_00150728: CPZOOM constructor (CM +0x520): CPLCY constructor, vtable D_002CD498, zoom limit 7, no zoom
 * target (-1), no sound references. */
#include "cm.h"

extern VTE D_002CD498[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPZOOM *func_00150728(CPZOOM *pcpzoom)
{
    func_0014FCA8(&pcpzoom->cplcy);
    pcpzoom->cplcy.pvt = D_002CD498;
    pcpzoom->rZoomMax = 7.0f;
    pcpzoom->uZoomTarget = -1.0f;
    pcpzoom->psndZoom = NULL;
    pcpzoom->psndUnkc4 = NULL;
    return pcpzoom;
}
