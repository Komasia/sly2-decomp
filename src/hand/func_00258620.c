/* CloneEmitter (0x258620): EMITTER virtual slot 40: XFM clone; the clone shares the EMITB, so take a reference. */
#include "emitter.h"

void func_002311B0(XFM *pxfm, XFM *pxfmBase);   /* XFM slot 40 (clone) */

void CloneEmitter__FP7EMITTERT0(EMITTER *pemitter, EMITTER *pemitterBase)
{
    func_002311B0(&pemitter->xfm, &pemitterBase->xfm);
    pemitter->pemitb->cref++;
}
