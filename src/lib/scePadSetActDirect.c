// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadSetActDirect (libpad): set the 6 actuator (vibration) values, sent to the IOP with the next transfer. */
typedef struct { int x0; int x4; int x8; unsigned char data[6]; } PadCmd;
typedef struct { unsigned char *buf; PadCmd *cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state */
unsigned char *scePadGetDmaStr(int port, int slot);
int _send_to_iop(int port, int slot);
int scePadSetActDirect(int port, int slot, const unsigned char *data)
{
    int i;
    PadCmd *c;
    if (scePadGetDmaStr(port, slot)[PADDMA_OK] != 1) return 0;
    c = D_004505D0[port][slot].cmd;
    for (i = 0; i < 6; i++) c->data[i] = data[i];
    c->x4 = 1;          /* actuator command */
    c->x8 = 6;          /* 6 data bytes */
    if (_send_to_iop(port, slot) != 1) return 0;
    return 1;
}
