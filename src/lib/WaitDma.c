// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* WaitDma (libdma): busy-wait until a DMA channel has finished (CHCR.STR clear); after about 16M polls report
   "libdma: sync timeout" and pause the channel. */
typedef struct { unsigned DIR:1; unsigned p0:1; unsigned MOD:2; unsigned ASP:2; unsigned TTE:1; unsigned TIE:1; unsigned STR:1; unsigned p1:7; unsigned TAG:16; } tD_CHCR;
typedef struct { tD_CHCR chcr; unsigned p0[3]; void *madr; unsigned p1[3]; unsigned qwc; unsigned p2[3]; void *tadr; } sceDmaChan;
extern char D_002AB368[];   /* "libdma: sync timeout\n" */
int scePrintf(const char *, ...);
int sceDmaPause(sceDmaChan *d);

void WaitDma(sceDmaChan *d)
{
    int timeout = 0x1000000;
    while (*(volatile unsigned *)d & D_CHCR_STR) {
        if (--timeout < 0) {
            scePrintf(D_002AB368);
            sceDmaPause(d);
        }
    }
}
