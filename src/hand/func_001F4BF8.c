/* MarkAloDirty__FP3ALO (0x1F4BF8): queue the SO's tree on queue 1 (MarkOxaDirty1__FP3ALO) and on queue 2 (D_003E11C4). */
#include "so.h"

void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);   /* append to a DL */
void MarkOxaDirty1__FP3ALO(SO *pso);
extern DL D_003E11C4;

// name: SafeHouse port (MarkAloDirty)
void MarkAloDirty__FP3ALO(SO *pso)
{
    SOTREE *ptree;

    MarkOxaDirty1__FP3ALO(pso);
    ptree = pso->ptree;
    if (ptree != NULL && !(ptree->grf & SOTREE_fQueued2)) {
        ptree->grf |= SOTREE_fQueued2;
        AppendDlEntry__FP2DLPv(&D_003E11C4, pso->ptree);
    }
}
