/* func_001518C8: constructor of the CM policy member at +0x5F0 (CPTURRET): CPLCY constructor, then its vtable (D_002CD3C0). */
#include "cm.h"

extern VTE D_002CD3C0[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPLCY *func_001518C8(CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002CD3C0;
    return pcplcy;
}
