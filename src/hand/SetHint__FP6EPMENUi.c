/* SetHint: the episode menu's hint: 0 selects the screen object part 0x5BE, 1 the part 0x5BD (0x213B00); the hint's
 * change time is the real clock's. Layout: SafeHouse port (frontend.cpp EPMENU). */
#include "clock.h"

struct EPMENU {
    /* 0x000 */ char pad0[0x12c];
    /* 0x12c */ int hint;    /* field: SafeHouse port */
    /* 0x130 */ float t130;  /* field: SafeHouse port */
};
void func_00213B00(struct EPMENU *pepmenu, int part);   /* SafeHouse: SelectScreenObjPart */   /* SafeHouse: SelectScreenObjPart */

// name: SafeHouse port (SetHint)
void SetHint__FP6EPMENUi(struct EPMENU *pepmenu, int n)
{
    if (pepmenu->hint != n) {
        if (n != 0) {
            if (n == 1)
                func_00213B00(pepmenu, 0x5BD);
        } else {
            func_00213B00(pepmenu, 0x5BE);
        }
        pepmenu->hint = n;
        pepmenu->t130 = g_clock.tReal;
    }
}
