/* func_0014FDE0: CPLOOK constructor (the look-around policy, CM +0x450): CPLCY constructor, vtable D_002CD4E0,
 * zoom limit 7, no sound references. */
#include "cm.h"

extern VTE D_002CD4E0[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPLOOK *func_0014FDE0(CPLOOK *pcplook)
{
    func_0014FCA8(&pcplook->cplcy);
    pcplook->cplcy.pvt = D_002CD4E0;
    pcplook->rZoomMax = 7.0f;
    pcplook->psndZoom = NULL;
    pcplook->psndUnk38 = NULL;
    return pcplook;
}
