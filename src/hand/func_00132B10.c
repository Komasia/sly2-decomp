/* FIsBasicDerivedFrom: whether the object's class (its descriptor from vt slot 6) is cid or derives from it: its
 * cid lies in [cid, cidMac) of the class table entry D_002BAAE8[cid]. Layout: include/cls.h CLS. */
#include "vtbl.h"
#include "cls.h"
struct BASIC { int pad[3]; VTENT *vt; };
extern CLS D_002BAAE8[];   /* the class descriptors by cid */
int FIsBasicDerivedFrom__FP5BASIC3CID(struct BASIC *pbasic, int cid)
{
    CLS *pcls = (CLS *)((void *(*)(void *))pbasic->vt[6].pfn)(VT_THIS(pbasic, &pbasic->vt[6]));
    int cidObj = pcls->cid;
    int f = 0;
    if (cidObj >= cid) {
        CLS *pclsBase = &D_002BAAE8[cid];
        f = cidObj < pclsBase->cidMac;
    }
    return f;
}
