/* func_001F6860 (0x1F6860): set or clear the SOTREE_fNoUpdate flag of the SO's tree, then func_001F4E28. */
#include "so.h"

void func_001F4E28(SO *pso);

void func_001F6860(SO *pso, int fNoUpdate)
{
    SOTREE *ptree = pso->ptree;

    if (ptree != NULL) {
        ptree->grf = (ptree->grf & ~SOTREE_fNoUpdate) | ((fNoUpdate & 1) * SOTREE_fNoUpdate);
        func_001F4E28(pso);
    }
}
