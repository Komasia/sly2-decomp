/* func_00149798 (0x149798): VOLBTN entry point: forward to the BTN function func_00148B18 on the embedded BTN (VOLBTN+0x130).
 * func_00149200 is the BUTTON twin. */
#include "button.h"

void func_00148B18(BTN *pbtn);

void func_00149798(VOLBTN *pvolbtn)
{
    func_00148B18(&pvolbtn->btn);
}
