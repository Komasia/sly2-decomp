/* SetHint: the episode menu's hint: 0 selects the screen object part 0x5BE, 1 the part 0x5BD (0x213B00); the hint's
 * change time is the real clock's. Layout: SafeHouse port (frontend.cpp EPMENU). */
#include "clock.h"

#include "h2_epmenu.h"
void func_00213B00(EPMENU *pepmenu, int part);   /* SafeHouse: SelectScreenObjPart */

// name: SafeHouse port (SetHint)
void SetHint__FP6EPMENUi(EPMENU *pepmenu, int n)
{
    if (pepmenu->hint != n) {
        if (n != 0) {
            if (n == 1)
                func_00213B00(pepmenu, 0x5BD);
        } else {
            func_00213B00(pepmenu, 0x5BE);
        }
        pepmenu->hint = n;
        pepmenu->tHint = g_clock.tReal;
    }
}
