// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadRead (libpad): copy the latest button data of (port, slot) to `rdata`; returns its length (0 if not open). */
typedef struct { unsigned char *buf; int cmd; int iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];     /* per port/slot state: DMA buffer, command buffers, open flag */
int DIntr(void);
int EIntr(void);
unsigned char *scePadGetDmaStr(int port, int slot);
void *s1_memcpy(void *, const void *, int) asm("memcpy");
int scePadRead(int port, int slot, unsigned char *rdata)
{
    int r;
    unsigned char *p;
    if (D_004505D0[port][slot].open == 0) return 0;
    r = DIntr();
    p = scePadGetDmaStr(port, slot);
    s1_memcpy(rdata, p, *(int *)(p + PADDMA_LEN));
    if (r == 1) EIntr();
    return *(int *)(p + PADDMA_LEN);
}
