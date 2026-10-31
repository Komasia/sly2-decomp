/* func_00149718 (0x149718): VOLBTN entry point: forward to the BTN function func_00148A78 on the embedded BTN (VOLBTN+0x130).
 * func_001490A0 is the BUTTON twin. */
#include "button.h"

void func_00148A78(BTN *pbtn);

void func_00149718(VOLBTN *pvolbtn)
{
    func_00148A78(&pvolbtn->btn);
}
