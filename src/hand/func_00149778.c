/* func_00149778 (0x149778): VOLBTN entry point: forward to the BTN function func_00148AF8 on the embedded BTN (VOLBTN+0x130).
 * func_001491E0 is the BUTTON twin. */
#include "button.h"

void func_00148AF8(BTN *pbtn);

void func_00149778(VOLBTN *pvolbtn)
{
    func_00148AF8(&pvolbtn->btn);
}
