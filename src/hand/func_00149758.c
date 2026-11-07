/* func_00149758 (0x149758): VOLBTN entry point: forward to the BTN function LeavePad__FP2LO on the embedded BTN (VOLBTN+0x130).
 * func_001490E0 is the BUTTON twin. */
#include "button.h"

void LeavePad__FP2LO(BTN *pbtn);

void func_00149758(VOLBTN *pvolbtn)
{
    LeavePad__FP2LO(&pvolbtn->btn);
}
