/* func_001F5078 (0x1F5078): if the SO has a tree, call its virtual slot 46 with 4 and, for a physical SO,
 * refresh both attachment transforms (func_00230598). */
#include "so.h"

void func_00230598(SO *pso, XF *pxf);

void func_001F5078(SO *pso)
{
    VTE *pvte;

    if (pso->ptree != NULL) {
        pvte = &pso->lo.pvt[47];   /* slot 46 */
        ((void (*)(void *, int))pvte->pfn)((char *)pso + pvte->d, 4);
        if (pso->psophys != NULL) {
            func_00230598(pso, pso->pxfUnk58);
            func_00230598(pso, pso->pxfUnk5c);
        }
    }
}
