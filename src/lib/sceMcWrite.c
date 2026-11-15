// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libmc_rpc.h"
/* sceMcWrite (libmc): write `size` bytes from `buf` to an open file. Asynchronous: returns 0 once the request is sent; sceMcSync gives the result. */
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int x4; int x8; int size; int x10; unsigned head; void *buf; int x1c; unsigned char data[16]; } McRwSend;
extern RpcCD D_00450880;    /* libmc RPC client */
extern McRwSend D_00450900;    /* libmc send buffer */
extern int D_00451E40[];    /* libmc receive buffer (command result) */
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
void func_00243ED8(void *);
int PollSema(int);
int SignalSema(int);
void FlushCache(int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceMcWrite(int fd, const void *buf, int size)
{
    unsigned i;
    if (D_00450880.server == 0)
        return MC_ERR_NOT_INIT;
    if (PollSema(D_002C8354) < 0)
        return MC_ERR_BUSY;
    D_00450900.fd = fd;
    if (size <= 16) {
        D_00450900.head = size;
        D_00450900.size = 0;
        D_00450900.buf = 0;
    } else {
        unsigned lo = (unsigned)buf - 16;
        unsigned n = (((unsigned)buf - 1) & 0xFFFFFFF0u) - lo;
        D_00450900.size = size - n;
        D_00450900.head = n;
        D_00450900.buf = (char *)buf + n;
    }
    for (i = 0; i < D_00450900.head; i++)
        D_00450900.data[i] = ((unsigned char *)buf)[i];
    FlushCache(0);
    if (sceSifCallRpc(&D_00450880, sceMcFuncNoWrite, 1 /* SIF_RPCM_NOWAIT */, &D_00450900, 0x30, D_00451E40, 4, func_00243ED8, 0) != 0) {
        SignalSema(D_002C8354);
        return MC_ERR_RPC;
    }
    D_002C8350 = sceMcFuncNoWrite;
    return 0;
}
