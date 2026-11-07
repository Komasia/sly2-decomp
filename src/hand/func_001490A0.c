/* func_001490A0 (0x1490A0): BUTTON entry point: forward to the BTN function SetTriggerState__FP2LOi on the embedded BTN (BUTTON+0x150).
 * func_00149718 is the VOLBTN twin. */
#include "button.h"

void SetTriggerState__FP2LOi(BTN *pbtn);

void func_001490A0(BUTTON *pbutton)
{
    SetTriggerState__FP2LOi(&pbutton->btn);
}
