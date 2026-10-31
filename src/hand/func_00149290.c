/* func_00149290 (0x149290): BUTTON entry point: forward to the BTN function func_00148B78 on the embedded BTN (BUTTON+0x150).
 * func_00149828 is the VOLBTN twin. */
#include "button.h"

void func_00148B78(BTN *pbtn);

void func_00149290(BUTTON *pbutton)
{
    func_00148B78(&pbutton->btn);
}
