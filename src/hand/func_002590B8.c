/* CloneExplo (0x2590B8): EXPLO virtual slot 40: XFM clone; the clone shares the EMITB, so take a reference. */
#include "emitter.h"

void func_002311B0(XFM *pxfm, XFM *pxfmBase);   /* XFM slot 40 (clone) */

void CloneExplo__FP5EXPLOT0(EXPLO *pexplo, EXPLO *pexploBase)
{
    func_002311B0(&pexplo->xfm, &pexploBase->xfm);
    pexplo->pemitb->cref++;
}
