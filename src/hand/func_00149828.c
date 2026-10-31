/* func_00149828 (0x149828): VOLBTN entry point: forward to the BTN function func_00148B78 on the embedded BTN (VOLBTN+0x130).
 * func_00149290 is the BUTTON twin. */
#include "button.h"

void func_00148B78(BTN *pbtn);

void func_00149828(VOLBTN *pvolbtn)
{
    func_00148B78(&pvolbtn->btn);
}
