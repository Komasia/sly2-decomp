// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadEnterPressMode (libpad): switch a DUALSHOCK 2 to pressure-sensitive mode (all 12 buttons, mask 0xFFF). */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
int scePadSetButtonInfo(int port, int slot, int info);
int scePadEnterPressMode(int port, int slot)
{
    if (D_004505D0[port][slot].open == 0) return 0;
    return scePadSetButtonInfo(port, slot, 0xFFF);
}
