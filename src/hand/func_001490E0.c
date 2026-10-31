/* func_001490E0 (0x1490E0): BUTTON entry point: forward to the BTN function func_00148860 on the embedded BTN (BUTTON+0x150).
 * func_00149758 is the VOLBTN twin. */
#include "button.h"

void func_00148860(BTN *pbtn);

void func_001490E0(BUTTON *pbutton)
{
    func_00148860(&pbutton->btn);
}
