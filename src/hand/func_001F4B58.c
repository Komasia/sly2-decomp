/* MarkOxaDirty1__FP3ALO (0x1F4B58): put the SO's tree on queue 1 (D_003E11B8) unless it is already queued there. */
#include "so.h"

void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);   /* append to a DL */
extern DL D_003E11B8;

// name: SafeHouse port (MarkOxaDirty1)
void MarkOxaDirty1__FP3ALO(SO *pso)
{
    SOTREE *ptree = pso->ptree;

    if (ptree != NULL && !(ptree->grf & SOTREE_fQueued1)) {
        ptree->grf |= SOTREE_fQueued1;
        AppendDlEntry__FP2DLPv(&D_003E11B8, pso->ptree);
    }
}
