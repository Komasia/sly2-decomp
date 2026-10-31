/* UpdateGrfjoytFromGrfusr (Sly 1 joy.c): what the game may read from the pad, given who is using it. Sly 2 checks two
 * more FUSR bits (0x10, 0x08) and resets D_002E0CBC when the pad is not readable by the game. */
#include "joy.h"

extern int D_002E0CBC;

void UpdateGrfjoytFromGrfusr()
{
    int grfusr = g_grfusr;

    if (grfusr & 0x10)
        g_grfjoyt = 5;
    else if (grfusr & 0xC)
        g_grfjoyt = 0;
    else if (grfusr & FUSR_Menu)
        g_grfjoyt = 5;          /* pause menu / dialog */
    else if (grfusr & FUSR_HandsOff)
        g_grfjoyt = 4;          /* cutscene */
    else
        g_grfjoyt = 7;          /* normal play */

    if (!(g_grfjoyt & 2))
        D_002E0CBC = 0xFFFF;
}
