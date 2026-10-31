/* func_001490C0 (0x1490C0): BUTTON entry point: forward to the BTN function func_001487A0 on the embedded BTN (BUTTON+0x150).
 * func_00149738 is the VOLBTN twin. */
#include "button.h"

void func_001487A0(BTN *pbtn);

void func_001490C0(BUTTON *pbutton)
{
    func_001487A0(&pbutton->btn);
}
