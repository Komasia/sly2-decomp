// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "sif_rpc.h"
/* sceSifCallRpc (libkernel sifrpc): call function `fno` of the IOP server bound to `client`, sending `ssize`
   bytes from `send` and receiving `rsize` bytes into `receive`. With SIF_RPCM_NOWAIT it returns at once and
   `end_function(end_param)` runs when the reply arrives; otherwise it waits on a semaphore. Returns 0, -1 (no
   free packet), -2 (send failed) or -3 (no semaphore). The volatile reads of end_param / rpc_id keep both
   loads ahead of the stores, as Sony's scheduler did. */
typedef struct {
    int sifcmd[4];      /* 0x00 SifCmdHeader */
    int rec_id;         /* 0x10 */
    void *pkt_addr;     /* 0x14 */
    int rpc_id;         /* 0x18 */
    void *client;       /* 0x1C */
    unsigned int fno;   /* 0x20 rpc_number */
    int ssize;          /* 0x24 */
    void *receive;      /* 0x28 */
    int rsize;          /* 0x2C */
    int rmode;          /* 0x30 1: reply wanted */
    void *server;       /* 0x34 */
} SifRpcCallPkt;
typedef void (*EndFunc)(void *);
typedef struct {
    void *paddr;        /* 0x00 packet in use */
    int pid;            /* 0x04 */
    int sema;           /* 0x08 */
    int mode;           /* 0x0C */
    void *command;      /* 0x10 */
    void *buff;         /* 0x14 server's receive buffer (from the bind) */
    void *gp;           /* 0x18 caller's $gp, restored around end_function */
    EndFunc end_function;   /* 0x1C */
    void *end_param;    /* 0x20 */
    void *server;       /* 0x24 */
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
extern char D_002AA9F8[];      /* semaphore option tag */
void *func_00236C28(void *);   /* _rpc_get_packet */
void func_00236CD0(void *);    /* free an RPC packet */
int CreateSema(struct SemaParam *);
int sceSifSendCmd(unsigned int, void *, int, void *, void *, int);
int DeleteSema(int);
int WaitSema(int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(SifRpcClientData *client, unsigned int fno, unsigned int mode, void *send, int ssize,
                  void *receive, int rsize, EndFunc end_function, void *end_param)
{
    SifRpcCallPkt *call;
    void *srv;
    struct SemaParam sema;
    void *gp;

    call = (SifRpcCallPkt *)func_00236C28(D_0044A600);
    if (call == 0) return -1;
    {
        void *ep = *(void * volatile *)&end_param;
        int pid = *(volatile int *)&call->rpc_id;
        client->end_param = ep;
        client->pid = pid;
    }
    client->paddr = call;
    client->end_function = end_function;
    __asm__ __volatile__("move %0, $gp" : "=r"(gp));
    client->gp = gp;
    call->fno = fno;
    call->ssize = ssize;
    call->receive = receive;
    call->rsize = rsize;
    call->pkt_addr = call;
    srv = client->server;
    call->client = client;
    call->server = srv;

    if (!(mode & SIF_RPCM_NOWBDC)) {
        if (send == receive) {
            sceSifWriteBackDCache(send, ssize < rsize ? rsize : ssize);
        } else {
            if (ssize > 0) sceSifWriteBackDCache(send, ssize);
            if (rsize > 0) sceSifWriteBackDCache(receive, rsize);
        }
    }

    if (mode & SIF_RPCM_NOWAIT) {
        if (end_function == 0) call->rmode = 0;
        else call->rmode = 1;
        client->sema = -1;
        if (sceSifSendCmd(SIF_CMD_RPC_CALL, call, SIF_RPC_PACKET_SIZE, send, client->buff, ssize) != 0)
            return 0;
        func_00236CD0(call);
        return -2;
    }
    sema.initCount = 0;
    sema.option = (unsigned int)D_002AA9F8;
    sema.maxCount = 1;
    client->sema = CreateSema(&sema);
    if (client->sema < 0) {
        func_00236CD0(call);
        return -3;
    }
    call->rmode = 1;
    if (sceSifSendCmd(SIF_CMD_RPC_CALL, call, SIF_RPC_PACKET_SIZE, send, client->buff, ssize) != 0) {
        WaitSema(client->sema);
        DeleteSema(client->sema);
        return 0;
    }
    DeleteSema(client->sema);
    func_00236CD0(call);
    return -2;
}
