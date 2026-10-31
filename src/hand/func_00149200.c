/* func_00149200 (0x149200): BUTTON entry point: forward to the BTN function func_00148B18 on the embedded BTN (BUTTON+0x150).
 * func_00149798 is the VOLBTN twin. */
#include "button.h"

void func_00148B18(BTN *pbtn);

void func_00149200(BUTTON *pbutton)
{
    func_00148B18(&pbutton->btn);
}
