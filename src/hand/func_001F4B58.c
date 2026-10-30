/* func_001F4B58 (0x1F4B58): put the SO's tree on queue 1 (D_003E11B8) unless it is already queued there. */
#include "so.h"

void func_0011A220(DL *pdl, void *pv);   /* append to a DL */
extern DL D_003E11B8;

void func_001F4B58(SO *pso)
{
    SOTREE *ptree = pso->ptree;

    if (ptree != NULL && !(ptree->grf & SOTREE_fQueued1)) {
        ptree->grf |= SOTREE_fQueued1;
        func_0011A220(&D_003E11B8, pso->ptree);
    }
}
