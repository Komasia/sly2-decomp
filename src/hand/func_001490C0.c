/* func_001490C0 (0x1490C0): BUTTON entry point: forward to the BTN function EnterPad__FP2LO on the embedded BTN (BUTTON+0x150).
 * func_00149738 is the VOLBTN twin. */
#include "button.h"

void EnterPad__FP2LO(BTN *pbtn);

void func_001490C0(BUTTON *pbutton)
{
    EnterPad__FP2LO(&pbutton->btn);
}
