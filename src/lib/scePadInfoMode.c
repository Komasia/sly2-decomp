// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadInfoMode (libpad): controller mode information (current id, extended id, mode offset, mode table). */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
typedef struct { unsigned char x0[0x30]; unsigned char act[6][4]; unsigned char x48[8]; unsigned short modes[10]; unsigned char phase; unsigned char id; unsigned char x66; unsigned char x67; unsigned char nmodes; unsigned char curmode; unsigned char nact; unsigned char x6B[5]; unsigned char state; unsigned char req; unsigned char ok; } PadData;
PadData *scePadGetDmaStr(int port, int slot);
int scePadInfoMode(int port, int slot, int term, int offs)
{
    PadData *p;
    if (D_004505D0[port][slot].open == 0) return 0;
    p = scePadGetDmaStr(port, slot);
    if (p->ok != 1) return 0;
    if (p->req == 2) return 0;
    switch (term) {
    case 1:                             /* InfoModeCurID */
        if (p->id == 0xF3) return 0;    /* config mode */
        return p->id >> 4;
    case 2:                             /* InfoModeCurExID */
        if (p->phase == 1) return 0;
        return p->modes[p->curmode];
    case 3:                             /* InfoModeCurExOffs */
        if (p->phase == 1) return 0;
        return p->curmode;
    case 4:                             /* InfoModeIdTable */
        if (p->phase == 1) return 0;
        if (offs == -1) return p->nmodes;
        if (offs < p->nmodes) return p->modes[offs];
        return 0;
    }
    return 0;
}
