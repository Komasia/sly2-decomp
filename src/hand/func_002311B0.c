/* CloneAlo (0x2311B0): ALO virtual slot 40: clone the LO part, then re-point the copied transform link at the
 * matching XF of this ALO's own hierarchy (virtual slot 49, func_00231220 for ALO) and invalidate the cached world
 * matrix (func_002313F0). */
#include "so.h"

void CloneLo__FP2LOT0(LO *plo, LO *ploBase);
void func_002313F0(ALO *palo);

void CloneAlo__FP3ALOT0(ALO *palo, ALO *paloBase)
{
    VTE *pvte;

    CloneLo__FP2LOT0(&palo->lo, &paloBase->lo);
    pvte = &paloBase->lo.pvt[50];   /* slot 49: map an XF link */
    ((void (*)(void *, ALO *, XF **))pvte->pfn)((char *)paloBase + pvte->d, paloBase, &paloBase->pxf);
    pvte = &palo->lo.pvt[50];
    ((void (*)(void *, ALO *, XF **))pvte->pfn)((char *)palo + pvte->d, paloBase, &palo->pxf);
    func_002313F0(palo);
}
