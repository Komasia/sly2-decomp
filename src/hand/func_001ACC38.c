/* func_001ACC38 (0x1ACC38): sets the memory card prompt's own state (+0x44) with its real time (+0x48); states 2 and 3
 * also forget the save manager's game slot (MC +0xFD50, include/h5_mc.h). */
struct MC { char pad[0xFD50]; int pslotGame; };
extern struct MC g_mc __asm__("D_002E65E0");
#include "clock.h"
struct S { char pad[0x44]; int state; float tState; };
void func_001ACC38(struct S *pprompt, int state)
{
    if (state == pprompt->state) return;
    switch (state) { case 2: case 3: g_mc.pslotGame = 0; }
    pprompt->state = state;
    pprompt->tState = g_clock.tReal;
}
