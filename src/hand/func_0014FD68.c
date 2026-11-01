/* func_0014FD68: constructor of the CM policy member at +0x3A0 (CMPART1): CPLCY constructor, then its vtable
 * (D_002CD528). */
#include "cm.h"

extern VTE D_002CD528[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPLCY *func_0014FD68(CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002CD528;
    return pcplcy;
}
