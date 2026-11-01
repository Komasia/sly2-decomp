/* func_0014FCA8: CPLCY constructor (camera policy base): installs the CPLCY vtable (D_002CD570). */
#include "cm.h"

extern VTE D_002CD570[];

CPLCY *func_0014FCA8(CPLCY *pcplcy)
{
    pcplcy->pvt = D_002CD570;
    return pcplcy;
}
