/* func_001F27F0 (0x1F27F0): make sure the SO has a SOTREE. The tree belongs to the root SO of the hierarchy
 * (func_001F2798); if the root has none yet it builds one through its virtual slot 52 and registers it with the
 * world, then this SO shares the root's tree. */
#include "so.h"

SO *func_001F2798(SO *pso);
void func_00134320(void *psw, SO *pso);
extern char D_003DD490[];   /* the world (SW) */

void func_001F27F0(SO *pso)
{
    SO *psoRoot;
    VTE *pvte;

    if (pso->ptree == NULL) {
        psoRoot = func_001F2798(pso);
        if (psoRoot->ptree == NULL) {
            pvte = &psoRoot->lo.pvt[53];   /* slot 52: allocate the tree record */
            psoRoot->ptree = ((SOTREE *(*)(void *))pvte->pfn)((char *)psoRoot + pvte->d);
            func_00134320(D_003DD490, psoRoot);
        }
        pso->ptree = psoRoot->ptree;
    }
}
