// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "libmc_rpc.h"
/* sceMcRead (libmc): read `size` bytes from an open file into `buf`. Asynchronous: returns 0 once the request is sent; sceMcSync gives the result. */
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int x4; int x8; int size; int x10; int x14; void *buf; void *param; } McRwSend;
extern RpcCD D_00450880;    /* libmc RPC client */
extern McRwSend D_00450900;    /* libmc send buffer */
extern int D_00451E40[];    /* libmc receive buffer (command result) */
extern char D_00450D80[];
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
void mceIntrReadFixAlign(void *);
int PollSema(int);
int SignalSema(int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceMcRead(int fd, void *buf, int size)
{
    if (D_00450880.server == 0)
        return MC_ERR_NOT_INIT;
    if (PollSema(D_002C8354) < 0)
        return MC_ERR_BUSY;
    D_00450900.fd = fd;
    D_00450900.buf = buf;
    D_00450900.size = size;
    D_00450900.param = D_00450D80;
    sceSifWriteBackDCache(buf, size);
    sceSifWriteBackDCache(D_00450D80, 0xC0);
    if (sceSifCallRpc(&D_00450880, sceMcFuncNoRead, 1 /* SIF_RPCM_NOWAIT */, &D_00450900, 0x30, D_00451E40, 4, mceIntrReadFixAlign, D_00450D80) == 0) {
        D_002C8350 = sceMcFuncNoRead;
        return 0;
    }
    SignalSema(D_002C8354);
    return MC_ERR_RPC;
}
