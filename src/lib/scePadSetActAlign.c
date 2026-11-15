// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadSetActAlign (libpad): map the 6 actuator data bytes to the controller's motors. 1 if the request was accepted. */
typedef struct { int cmd; int port; int slot; unsigned char data[8]; int result; char pad[0x80 - 0x18]; } PadBuf;
extern PadBuf D_004507C0;   /* RPC request/reply buffer */
extern char D_00450580[];   /* padman RPC client */
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int scePadSetReqState(int port, int slot, int state);
int scePadSetActAlign(int port, int slot, const unsigned char *data)
{
    int i;
    int r;
    PadBuf *p = &D_004507C0;
    D_004507C0.cmd = PAD_RPCCMD_SET_ACTALIGN;
    p->port = port;
    p->slot = slot;
    for (i = 0; i < 6; i++)
        p->data[i] = data[i];
    if (sceSifCallRpc(D_00450580, 1, 0, p, 0x80, p, 0x80, 0, 0) < 0)
        return 0;
    r = p->result;
    if (r == 1) {
        scePadSetReqState(port, slot, scePadReqStateBusy);
        r = p->result;
    }
    return r;
}
