/* class: BASIC (so.h, cls.h; called by 0x16EA80): a copy of the object - a new object of its class (the descriptor
 * from virtual slot 5, CLS::pfnNew), its CLS::cb bytes copied, the copy's two lists (+0x34, +0x40) reset, and the
 * copy appended to the list D_003E159C. */
#include "so.h"
#include "cls.h"

void CopyAb__FPvT0Ui(void *pvDst, void *pvSrc, unsigned int cb);
void func_0011A060(void *pdl);
void func_0011A058(void *pdl);
void func_0011A070(void *pdl, void *pv);   /* append */
extern char D_003E159C[];

BASIC *func_001ED850(BASIC *pbasic)
{
    VTE *pvt = pbasic->pvt;
    CLS *pcls = ((CLS *(*)(void *))pvt[6].pfn)((char *)pbasic + pvt[6].d);
    BASIC *pbasicNew = (BASIC *)pcls->pfnNew();

    CopyAb__FPvT0Ui(pbasicNew, pbasic, pcls->cb);
    func_0011A060((char *)pbasicNew + 0x34);
    func_0011A058((char *)pbasicNew + 0x40);
    func_0011A070(D_003E159C, pbasicNew);
    return pbasicNew;
}
