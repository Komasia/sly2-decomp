/* PoxaEnsure__FP3ALO (0x1F27F0): make sure the SO has a SOTREE. The tree belongs to the root SO of the hierarchy
 * (PaloPhysRoot__FP3ALO); if the root has none yet it builds one through its virtual slot 52 and registers it with the
 * world, then this SO shares the root's tree. */
#include "so.h"

SO *PaloPhysRoot__FP3ALO(SO *pso);
void RecalcSwOxfFilterForObject__FP2SWP2SO(void *psw, SO *pso);
extern char g_sw[];   /* the world (SW) */

// name: SafeHouse port (PoxaEnsure)
void PoxaEnsure__FP3ALO(SO *pso)
{
    SO *psoRoot;
    VTE *pvte;

    if (pso->ptree == NULL) {
        psoRoot = PaloPhysRoot__FP3ALO(pso);
        if (psoRoot->ptree == NULL) {
            pvte = &psoRoot->lo.pvt[53];   /* slot 52: allocate the tree record */
            psoRoot->ptree = ((SOTREE *(*)(void *))pvte->pfn)((char *)psoRoot + pvte->d);
            RecalcSwOxfFilterForObject__FP2SWP2SO(g_sw, psoRoot);
        }
        pso->ptree = psoRoot->ptree;
    }
}
