// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* sceSifBindRpc (libkernel sifrpc): bind `client` to the IOP RPC server `request`. Unless SIF_RPCM_NOWAIT,
   waits on a semaphore until _request_end has filled in client->serve. Returns 0, -1 (no free packet),
   -2 (send failed) or -3 (no semaphore). */
typedef struct {
    int sifcmd[4];          /* 0x00 SifCmdHeader */
    int rec_id;             /* 0x10 */
    void *pkt_addr;         /* 0x14 */
    int rpc_id;             /* 0x18 */
    void *client;           /* 0x1C */
    unsigned int sid;       /* 0x20 */
} SifRpcBindPkt;
typedef struct {
    void *paddr;            /* 0x00 packet in use */
    int pid;                /* 0x04 */
    int sema;               /* 0x08 */
    int mode;               /* 0x0C */
    void *command;          /* 0x10 */
    int buff, gp, func, para;   /* 0x14 */
    void *serve;            /* 0x24 */
} SifRpcClientData;
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern char D_0044A600[];      /* the RPC module state (SifRpcData) */
extern char D_002AA9E8[];      /* semaphore option tag */
void *func_00236C28(void *);   /* _rpc_get_packet */
void func_00236CD0(void *);    /* free an RPC packet */
int CreateSema(struct SemaParam *);
int sceSifSendCmd(unsigned int, void *, int, void *, void *, int);
int DeleteSema(int);
int WaitSema(int);
int sceSifBindRpc(SifRpcClientData *client, unsigned int request, unsigned int mode)
{
    SifRpcBindPkt *bind;
    struct SemaParam sema;

    client->command = 0;
    client->serve = 0;
    bind = (SifRpcBindPkt *)func_00236C28(D_0044A600);
    if (bind == 0) return -1;
    client->paddr = bind;
    client->pid = bind->rpc_id;
    bind->sid = request;
    bind->pkt_addr = bind;
    bind->client = client;

    if (!(mode & SIF_RPCM_NOWAIT)) {
        sema.maxCount = 1;
        sema.option = (unsigned int)D_002AA9E8;
        sema.initCount = 0;
        client->sema = CreateSema(&sema);
        if (client->sema < 0) {
            func_00236CD0(bind);
            return -3;
        }
        if (sceSifSendCmd(SIF_CMD_RPC_BIND, bind, SIF_RPC_PACKET_SIZE, 0, 0, 0) == 0) {
            func_00236CD0(bind);
            DeleteSema(client->sema);
            return -2;
        }
        WaitSema(client->sema);
        DeleteSema(client->sema);
    } else {
        client->sema = -1;
        if (sceSifSendCmd(SIF_CMD_RPC_BIND, bind, SIF_RPC_PACKET_SIZE, 0, 0, 0) == 0) {
            func_00236CD0(bind);
            return -2;
        }
    }
    return 0;
}
