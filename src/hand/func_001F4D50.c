/* UnmarkAloDirty__FP3ALO (0x1F4D50): undo MarkAloDirty__FP3ALO - take the SO's tree off queue 1 (UnmarkOxaDirty1__FP3ALO) and off
 * queue 2 (D_003E11C4). */
#include "so.h"

void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
void UnmarkOxaDirty1__FP3ALO(SO *pso);
extern DL D_003E11C4;

// name: SafeHouse port (UnmarkAloDirty)
void UnmarkAloDirty__FP3ALO(SO *pso)
{
    SOTREE *ptree;

    UnmarkOxaDirty1__FP3ALO(pso);
    ptree = pso->ptree;
    if (ptree != NULL && (ptree->grf & SOTREE_fQueued2)) {
        ptree->grf &= ~SOTREE_fQueued2;
        RemoveDlEntry__FP2DLPv(&D_003E11C4, pso->ptree);
    }
}
