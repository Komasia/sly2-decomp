/* func_001F4D50 (0x1F4D50): undo func_001F4BF8 - take the SO's tree off queue 1 (func_001F4BA8) and off
 * queue 2 (D_003E11C4). */
#include "so.h"

void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
void func_001F4BA8(SO *pso);
extern DL D_003E11C4;

void func_001F4D50(SO *pso)
{
    SOTREE *ptree;

    func_001F4BA8(pso);
    ptree = pso->ptree;
    if (ptree != NULL && (ptree->grf & SOTREE_fQueued2)) {
        ptree->grf &= ~SOTREE_fQueued2;
        RemoveDlEntry__FP2DLPv(&D_003E11C4, pso->ptree);
    }
}
