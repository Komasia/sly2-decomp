/* NPoEnabled__FP2LO (0x1C4080): the state of the PO's controller, -1 when it has none. */
#include "po.h"

// name: SafeHouse port (NPoEnabled)
int NPoEnabled__FP2LO(PO *ppo)
{
    POCTL *pctl = ppo->pctl;
    int nState = -1;

    if (pctl != NULL)
        nState = pctl->nState;
    return nState;
}
