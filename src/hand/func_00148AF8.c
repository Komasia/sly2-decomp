/* class: BTN (button.h; reached through the BUTTON / VOLBTN entry points 0x1491E0 / 0x149778 with the other
 * arguments unchanged): a pair of values appended to the button's list at +0x4 (0x148620: 8 pairs at most). */
#include "button.h"

int func_00148620(void *plist, int n0, int n1);

void func_00148AF8(BTN *pbtn, int n0, int n1)
{
    func_00148620(pbtn->unk_0x04, n0, n1);
}
