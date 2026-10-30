/* func_001C4640 (0x1C4640): set the controller state; entering state 1 marks all buttons as freshly pressed. */
#include "po.h"

void func_001C4640(POCTL *pctl, int nState)
{
    pctl->nState = nState;
    if (nState == 1)
        pctl->grfPressed = 0xFFFF;
}
