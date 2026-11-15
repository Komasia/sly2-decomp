// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "libmc_rpc.h"
/* sceMcClose (libmc): close a memory card file. Asynchronous: returns 0 once the request is sent; sceMcSync gives the result. */
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_00450880;    /* libmc RPC client */
extern int D_00450900[];    /* libmc send buffer */
extern int D_00451E40[];    /* libmc receive buffer (command result) */
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
void func_00243ED8(void *);
int PollSema(int);
int SignalSema(int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceMcClose(int fd)
{
    if (D_00450880.server == 0)
        return MC_ERR_NOT_INIT;
    if (PollSema(D_002C8354) < 0)
        return MC_ERR_BUSY;
    D_00450900[0] = fd;
    if (sceSifCallRpc(&D_00450880, sceMcFuncNoClose, 1 /* SIF_RPCM_NOWAIT */, D_00450900, 0x30, D_00451E40, 4, func_00243ED8, 0) == 0) {
        D_002C8350 = sceMcFuncNoClose;
        return 0;
    }
    SignalSema(D_002C8354);
    return MC_ERR_RPC;
}
