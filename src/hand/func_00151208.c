/* func_00151208: constructor of CPHANG (CM +0x4C0): CPLCY constructor, then its vtable (D_002CD450). */
#include "cm.h"

extern VTE D_002CD450[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);

CPLCY *func_00151208(CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002CD450;
    return pcplcy;
}
