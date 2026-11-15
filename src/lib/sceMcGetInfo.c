// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libmc_rpc.h"
/* sceMcGetInfo (libmc): card type, free clusters and format state of (port, slot); each output pointer may be 0. Asynchronous: returns 0 once the request is sent; sceMcSync gives the result. */
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int port; int slot; int format; int free; int type; int x18; void *param; } McInfoSend;
extern RpcCD D_00450880;    /* libmc RPC client */
extern McInfoSend D_00450900;    /* libmc send buffer */
extern int D_00451E40[];    /* libmc receive buffer (command result) */
extern char D_00450D80[];
extern int *D_004508A8;
extern int *D_004508AC;
extern int *D_004508B0;
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
void mceGetInfoApdx(void *);
int PollSema(int);
int SignalSema(int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    if (D_00450880.server == 0)
        return MC_ERR_NOT_INIT;
    if (PollSema(D_002C8354) < 0)
        return MC_ERR_BUSY;
    D_00450900.port = port;
    D_00450900.slot = slot;
    D_00450900.param = D_00450D80;
    if (type) D_00450900.type = 1; else D_00450900.type = 0;
    if (free) D_00450900.free = 1; else D_00450900.free = 0;
    if (format) D_00450900.format = 1; else D_00450900.format = 0;
    D_004508A8 = type;
    D_004508AC = free;
    D_004508B0 = format;
    sceSifWriteBackDCache(D_00450D80, 0xC0);
    if (sceSifCallRpc(&D_00450880, sceMcFuncNoCardInfo, 1 /* SIF_RPCM_NOWAIT */, &D_00450900, 0x30, D_00451E40, 4, mceGetInfoApdx, D_00450D80) != 0) {
        SignalSema(D_002C8354);
        return MC_ERR_RPC;
    }
    D_002C8350 = sceMcFuncNoCardInfo;
    return 0;
}
