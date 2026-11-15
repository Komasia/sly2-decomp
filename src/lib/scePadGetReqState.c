// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadGetReqState (libpad): state of the last mode/actuator request (scePadReqStateComplete / Faild / Busy). */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
unsigned char *scePadGetDmaStr(int port, int slot);
int scePadGetReqState(int port, int slot)
{
    if (D_004505D0[port][slot].open == 0) return 0;
    return scePadGetDmaStr(port, slot)[PADDMA_REQSTATE];
}
