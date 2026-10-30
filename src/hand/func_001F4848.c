/* func_001F4848 (0x1F4848): pass the first attachment transform (SO::pxfUnk58) to func_0022FCC8 together with the
 * root transform. func_001F4870 is the same for SO::pxfUnk5c. */
#include "so.h"

void func_0022FCC8(int n, XF *pxfRoot, qword qwPos);

void func_001F4848(SO *pso)
{
    XF *pxf = pso->pxfUnk58;

    func_0022FCC8(pxf->nUnkA0, pso->pxfRoot, pxf->qwPosUnkB0);
}
