// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadGetButtonMask (libpad): mask of the pressure-sensitive buttons the controller reports (0x3FFFF = all), 0 if unknown. */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
unsigned char *scePadGetDmaStr(int port, int slot);
int scePadGetButtonMask(int port, int slot)
{
    unsigned char *p;
    if (D_004505D0[port][slot].open == 0) return 0;
    p = scePadGetDmaStr(port, slot);
    if (p[PADDMA_OK] != 1) return 0;
    if (p[PADDMA_PHASE] < 2) return 0;
    if (p[PADDMA_ACTPHASE] < 2) return 0;
    return (long)p[PADDMA_BTNMASK] + ((long)p[PADDMA_BTNMASK + 1] << 8) + ((long)p[PADDMA_BTNMASK + 2] << 16) +
           ((long)p[PADDMA_BTNMASK + 3] << 24);
}
