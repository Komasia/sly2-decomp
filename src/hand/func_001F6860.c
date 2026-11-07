/* SetAloContactsOff__FP3ALOi (0x1F6860): set or clear the SOTREE_fNoUpdate flag of the SO's tree, then DetachAloContacts__FP3ALO. */
#include "so.h"

void DetachAloContacts__FP3ALO(SO *pso);

// name: SafeHouse port (SetAloContactsOff)
void SetAloContactsOff__FP3ALOi(SO *pso, int fNoUpdate)
{
    SOTREE *ptree = pso->ptree;

    if (ptree != NULL) {
        ptree->grf = (ptree->grf & ~SOTREE_fNoUpdate) | ((fNoUpdate & 1) * SOTREE_fNoUpdate);
        DetachAloContacts__FP3ALO(pso);
    }
}
