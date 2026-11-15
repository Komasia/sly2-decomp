// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadGetDmaStr (libpad): the newer of the two frames the IOP DMAs into the port's buffer. */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
typedef struct { char x[0x58]; int frame; char y[0x24]; } PadData;
void func_00234F48(void *, void *);     /* invalidate the data cache over [start, end] */
unsigned char *scePadGetDmaStr(int port, int slot)
{
    PadData *p = (PadData *)D_004505D0[port][slot].buf;
    func_00234F48(p, (char *)p + 0xFF);
    { int id = 0; if (p[0].frame < p[1].frame) id = 1; return (unsigned char *)(p + id); }     /* newer frame */
}
