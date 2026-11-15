// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "libmc_rpc.h"
/* sceMcGetDir (libmc): list directory entries matching `name` into `table` (up to maxent). Asynchronous: returns 0 once the request is sent; sceMcSync gives the result. */
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int port; int slot; int flags; int size; int offset; char name[0x400]; } McSend;
extern RpcCD D_00450880;    /* libmc RPC client */
extern McSend D_00450930;    /* open/mkdir/delete arguments */
extern int D_00451E40[];    /* libmc receive buffer (command result) */
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
void func_00243ED8(void *);
int PollSema(int);
int SignalSema(int);
char *func_00233638(char *, const char *, unsigned int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table)
{
    if (D_00450880.server == 0)
        return MC_ERR_NOT_INIT;
    if (PollSema(D_002C8354) < 0)
        return MC_ERR_BUSY;
    if (name == 0 || name[0] == 0) {
        SignalSema(D_002C8354);
        return MC_ERR_BAD_NAME;
    }
    D_00450930.port = port;
    D_00450930.slot = slot;
    D_00450930.flags = mode;
    D_00450930.size = maxent;
    D_00450930.offset = (int)table;
    func_00233638(D_00450930.name, name, 0x3FF);
    D_00450930.name[0x3FF] = 0;
    if (maxent >= 0) sceSifWriteBackDCache(table, maxent << 6);
    if (sceSifCallRpc(&D_00450880, sceMcFuncNoGetDir, 1 /* SIF_RPCM_NOWAIT */, &D_00450930, 0x414, D_00451E40, 4, func_00243ED8, 0) == 0) {
        D_002C8350 = sceMcFuncNoGetDir;
        return 0;
    }
    SignalSema(D_002C8354);
    return MC_ERR_RPC;
}
