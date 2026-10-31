/* func_00149270 (0x149270): BUTTON entry point: forward to the BTN function func_00148B38 on the embedded BTN (BUTTON+0x150).
 * func_00149808 is the VOLBTN twin. */
#include "button.h"

void func_00148B38(BTN *pbtn);

void func_00149270(BUTTON *pbutton)
{
    func_00148B38(&pbutton->btn);
}
