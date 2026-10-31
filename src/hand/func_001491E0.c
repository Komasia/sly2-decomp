/* func_001491E0 (0x1491E0): BUTTON entry point: forward to the BTN function func_00148AF8 on the embedded BTN (BUTTON+0x150).
 * func_00149778 is the VOLBTN twin. */
#include "button.h"

void func_00148AF8(BTN *pbtn);

void func_001491E0(BUTTON *pbutton)
{
    func_00148AF8(&pbutton->btn);
}
