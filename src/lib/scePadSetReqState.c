// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadSetReqState (libpad): overwrite the request state in the current frame. */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
int DIntr(void);
int EIntr(void);
unsigned char *scePadGetDmaStr(int port, int slot);
int scePadSetReqState(int port, int slot, int state)
{
    int r;
    if (D_004505D0[port][slot].open == 0) return 0;
    r = DIntr();
    scePadGetDmaStr(port, slot)[PADDMA_REQSTATE] = state;
    if (r == 1) EIntr();
    return 1;
}
