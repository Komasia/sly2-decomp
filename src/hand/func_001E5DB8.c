/* ClonePath: clone a path object (the base clone 0x2311B0); a clone that copied a rope simulation pointer drops it
 * and makes its own (PropeEnsure). Layout: crv.h CRV. */
#include "crv.h"

void func_002311B0(CRV *pcrv);
struct ROPE *PropeEnsure__FP2LOi(CRV *pcrv, int f);

// name: vt slot 41 = Clone (CloneLo / CloneEmitter / CloneVolbtn in the same slot) of PATH (cid 0x0A)
void ClonePath__FP4PATHT0(CRV *pcrv)
{
    func_002311B0(pcrv);
    if (pcrv->prope) {
        pcrv->prope = 0;
        PropeEnsure__FP2LOi(pcrv, 0);
    }
}
