/* func_001490A0 (0x1490A0): BUTTON entry point: forward to the BTN function func_00148A78 on the embedded BTN (BUTTON+0x150).
 * func_00149718 is the VOLBTN twin. */
#include "button.h"

void func_00148A78(BTN *pbtn);

void func_001490A0(BUTTON *pbutton)
{
    func_00148A78(&pbutton->btn);
}
