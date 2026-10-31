/* func_002311B0 (0x2311B0): XFM virtual slot 40: clone the LO part, then re-point the copied transform link at the
 * matching XF of this XFM's own hierarchy (virtual slot 49, func_00231220 for XFM) and invalidate the cached world
 * matrix (func_002313F0). */
#include "so.h"

void CloneLo__FP2LOT0(LO *plo, LO *ploBase);
void func_002313F0(XFM *pxfm);

void func_002311B0(XFM *pxfm, XFM *pxfmBase)
{
    VTE *pvte;

    CloneLo__FP2LOT0(&pxfm->lo, &pxfmBase->lo);
    pvte = &pxfmBase->lo.pvt[50];   /* slot 49: map an XF link */
    ((void (*)(void *, XFM *, XF **))pvte->pfn)((char *)pxfmBase + pvte->d, pxfmBase, &pxfmBase->pxf);
    pvte = &pxfm->lo.pvt[50];
    ((void (*)(void *, XFM *, XF **))pvte->pfn)((char *)pxfm + pvte->d, pxfmBase, &pxfm->pxf);
    func_002313F0(pxfm);
}
