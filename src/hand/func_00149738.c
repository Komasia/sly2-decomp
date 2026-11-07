/* func_00149738 (0x149738): VOLBTN entry point: forward to the BTN function EnterPad__FP2LO on the embedded BTN (VOLBTN+0x130).
 * func_001490C0 is the BUTTON twin. */
#include "button.h"

void EnterPad__FP2LO(BTN *pbtn);

void func_00149738(VOLBTN *pvolbtn)
{
    EnterPad__FP2LO(&pvolbtn->btn);
}
