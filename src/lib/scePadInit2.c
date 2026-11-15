// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadInit2 (libpad): mark every port closed, initialise the IOP side and install the DMA-update handler. */
typedef struct { int a, b, c, d, e, f, g; } PadSlot;
extern PadSlot D_004505D0[2][4];   /* per port/slot state (e = open) */
extern char D_00450580[];   /* padman RPC client */
extern int D_004507C0[];    /* RPC request/reply buffer (0x80 bytes) */
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int DIntr(void);
int EIntr(void);
void sceSifAddCmdHandler(int, void *, void *);
int _pad_intr_hdr(void *);
int scePadInit2(int mode)
{
    int i;
    int s;
    for (i = 0; i < 4; i++) {
        D_004505D0[0][i].e = 0;
        D_004505D0[0][i].g = 0;
        D_004505D0[0][i].f = 0;
        D_004505D0[1][i].e = 0;
        D_004505D0[1][i].g = 0;
        D_004505D0[1][i].f = 0;
    }
    D_004507C0[0] = PAD_RPCCMD_INIT;
    D_004507C0[4] = 0;
    if (sceSifCallRpc(D_00450580, 1, 0, D_004507C0, 0x80, D_004507C0, 0x80, 0, 0) < 0)
        return 0;
    s = DIntr();
    sceSifAddCmdHandler(PAD_SIF_CMD_INTR, _pad_intr_hdr, 0);
    if (s == 1) EIntr();
    return D_004507C0[3];
}
