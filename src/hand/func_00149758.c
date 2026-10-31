/* func_00149758 (0x149758): VOLBTN entry point: forward to the BTN function func_00148860 on the embedded BTN (VOLBTN+0x130).
 * func_001490E0 is the BUTTON twin. */
#include "button.h"

void func_00148860(BTN *pbtn);

void func_00149758(VOLBTN *pvolbtn)
{
    func_00148860(&pvolbtn->btn);
}
