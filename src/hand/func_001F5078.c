/* WakeAlo__FP3ALO (0x1F5078): if the SO has a tree, call its virtual slot 46 with 4 and, for a physical SO,
 * refresh both attachment transforms (HoldXfMode). */
#include "so.h"

void HoldXfMode(SO *pso, XF *pxf);

// name: SafeHouse port (WakeAlo)
void WakeAlo__FP3ALO(SO *pso)
{
    VTENT *pvte;

    if (pso->ptree != NULL) {
        pvte = &pso->lo.pvt[47];   /* slot 46 */
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pso, pvte), 4);
        if (pso->psophys != NULL) {
            HoldXfMode(pso, pso->pxfUnk58);
            HoldXfMode(pso, pso->pxfUnk5c);
        }
    }
}
