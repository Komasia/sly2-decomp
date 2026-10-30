/* func_001F4BF8 (0x1F4BF8): queue the SO's tree on queue 1 (func_001F4B58) and on queue 2 (D_003E11C4). */
#include "so.h"

void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);   /* append to a DL */
void func_001F4B58(SO *pso);
extern DL D_003E11C4;

void func_001F4BF8(SO *pso)
{
    SOTREE *ptree;

    func_001F4B58(pso);
    ptree = pso->ptree;
    if (ptree != NULL && !(ptree->grf & SOTREE_fQueued2)) {
        ptree->grf |= SOTREE_fQueued2;
        AppendDlEntry__FP2DLPv(&D_003E11C4, pso->ptree);
    }
}
