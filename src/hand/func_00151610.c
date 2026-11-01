/* func_00151610: constructor of the CM policy member at +0x500 (CPCAMBLEND): CPLCY constructor, then its vtable (D_002CD408). */
#include "cm.h"

extern VTE D_002CD408[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPLCY *func_00151610(CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002CD408;
    return pcplcy;
}
