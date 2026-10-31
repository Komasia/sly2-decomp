/* func_00149738 (0x149738): VOLBTN entry point: forward to the BTN function func_001487A0 on the embedded BTN (VOLBTN+0x130).
 * func_001490C0 is the BUTTON twin. */
#include "button.h"

void func_001487A0(BTN *pbtn);

void func_00149738(VOLBTN *pvolbtn)
{
    func_001487A0(&pvolbtn->btn);
}
