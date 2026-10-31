/* InitJoy (Sly 1 joy.c): open the pad port; Sly 2's JOY holds the libpad DMA buffer and the RUMBLE itself. */
#include "joy.h"

extern "C" int scePadPortOpen(int port, int slot, void *addr);   /* func_00243088 */

void InitJoy(JOY *pjoy, int nPort, int nSlot)
{
    SetJoyJoys(pjoy, JOYS_Searching, JOYK_Unknown);
    pjoy->nPort = nPort;
    pjoy->nSlot = nSlot;
    scePadPortOpen(nPort, nSlot, pjoy);
    pjoy->fRumbleEnabled = 1;
    pjoy->uDpad = 1.0f;
}
