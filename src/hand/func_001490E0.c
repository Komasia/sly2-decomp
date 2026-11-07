/* func_001490E0 (0x1490E0): BUTTON entry point: forward to the BTN function LeavePad__FP2LO on the embedded BTN (BUTTON+0x150).
 * func_00149758 is the VOLBTN twin. */
#include "button.h"

void LeavePad__FP2LO(BTN *pbtn);

void func_001490E0(BUTTON *pbutton)
{
    LeavePad__FP2LO(&pbutton->btn);
}
