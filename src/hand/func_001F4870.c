/* func_001F4870 (0x1F4870): func_001F4848 for the second attachment transform (SO::pxfUnk5c). */
#include "so.h"

void func_0022FCC8(int n, XF *pxfRoot, qword qwPos);

void func_001F4870(SO *pso)
{
    XF *pxf = pso->pxfUnk5c;

    func_0022FCC8(pxf->nUnkA0, pso->pxfRoot, pxf->qwPosUnkB0);
}
