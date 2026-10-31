/* func_00149808 (0x149808): VOLBTN entry point: forward to the BTN function func_00148B38 on the embedded BTN (VOLBTN+0x130).
 * func_00149270 is the BUTTON twin. */
#include "button.h"

void func_00148B38(BTN *pbtn);

void func_00149808(VOLBTN *pvolbtn)
{
    func_00148B38(&pvolbtn->btn);
}
