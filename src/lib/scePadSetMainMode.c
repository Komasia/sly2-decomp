// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadSetMainMode (libpad): select mode `offs` (digital / analog) and lock it if `lock` == 3. 1 if the request was accepted. */
extern char D_00450580[];   /* padman RPC client */
extern int D_004507C0[];    /* RPC request/reply buffer (0x80 bytes) */
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
void scePadSetReqState(int, int, int);
int scePadSetMainMode(int port, int slot, int offs, int lock)
{
    int r;
    D_004507C0[0] = PAD_RPCCMD_SET_MMODE;
    D_004507C0[1] = port;
    D_004507C0[2] = slot;
    D_004507C0[3] = offs;
    D_004507C0[4] = lock;
    if (sceSifCallRpc(D_00450580, 1, 0, D_004507C0, 0x80, D_004507C0, 0x80, 0, 0) < 0)
        return 0;
    r = D_004507C0[5];
    if (r == 1) {
        scePadSetReqState(port, slot, scePadReqStateBusy);
        r = D_004507C0[5];
    }
    return r;
}
