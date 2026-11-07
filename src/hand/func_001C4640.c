/* SetPadctlControl__FP6PADCTLi (0x1C4640): set the controller state; entering state 1 marks all buttons as freshly pressed. */
#include "po.h"

// name: SafeHouse port (SetPadctlControl)
void SetPadctlControl__FP6PADCTLi(POCTL *pctl, int nState)
{
    pctl->nState = nState;
    if (nState == 1)
        pctl->grfPressed = 0xFFFF;
}
