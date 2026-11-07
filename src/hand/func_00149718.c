/* func_00149718 (0x149718): VOLBTN entry point: forward to the BTN function SetTriggerState__FP2LOi on the embedded BTN (VOLBTN+0x130).
 * func_001490A0 is the BUTTON twin. */
#include "button.h"

void SetTriggerState__FP2LOi(BTN *pbtn);

void func_00149718(VOLBTN *pvolbtn)
{
    SetTriggerState__FP2LOi(&pvolbtn->btn);
}
