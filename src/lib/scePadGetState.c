// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadGetState (libpad): connection state of (port, slot); a stable pad with a request pending reports ExecCmd. */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
int DIntr(void);
int EIntr(void);
unsigned char *scePadGetDmaStr(int port, int slot);
int scePadGetState(int port, int slot)
{
    int r;
    unsigned char *p;
    if (D_004505D0[port][slot].open == 0) return PAD_ERR_NOT_OPEN;
    r = DIntr();
    p = scePadGetDmaStr(port, slot);
    if (p[PADDMA_STATE] == scePadStateStable && p[PADDMA_REQSTATE] == scePadReqStateBusy) {
        if (r == 1) EIntr();
        return scePadStateExecCmd;
    }
    if (r == 1) EIntr();
    return p[PADDMA_STATE];
}
