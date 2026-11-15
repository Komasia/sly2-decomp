// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* _request_end (libkernel sifrpc): SIF_CMD_RPC_END handler: an RPC we started has finished. A call runs the
   client's end function (with the client's $gp); a bind stores the server and buffer it got. Then wake the
   waiting thread and free the packet. */
typedef struct {
    void *paddr;                /* 0x00 packet in use */
    int pid;                    /* 0x04 */
    int sema;                   /* 0x08 semaphore of a waiting call, -1 for none */
    int mode;                   /* 0x0C */
    int command;                /* 0x10 */
    int buff;                   /* 0x14 */
    void *gp;                   /* 0x18 caller's $gp for the end function */
    void (*func)(void *);       /* 0x1C end function */
    void *para;                 /* 0x20 */
    int serve;                  /* 0x24 */
} SifRpcClientData;
typedef struct {
    int pad[7];
    SifRpcClientData *client;   /* 0x1C */
    unsigned int cid;           /* 0x20 command that ended */
    int server;                 /* 0x24 */
    int buff;                   /* 0x28 */
} SifRpcEndPkt;
void iSignalSema(int);
void func_00236CD0(void *);     /* free an RPC packet */
static inline void *SetGP(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}

void _request_end(SifRpcEndPkt *rend)
{
    SifRpcClientData *client;
    switch (rend->cid) {
    case SIF_CMD_RPC_CALL:
        client = rend->client;
        if (client->func) {
            void *gp = SetGP(client->gp);
            client->func(client->para);
            SetGP(gp);
            client = rend->client;
        }
        break;
    case SIF_CMD_RPC_BIND:
        client = rend->client;
        client->serve = rend->server;
        client->buff = rend->buff;
        break;
    case 0x8000000B:
    default:
        client = rend->client;
        break;
    }
    if (client->sema >= 0)
        iSignalSema(client->sema);
    func_00236CD0(client->paddr);
    client->paddr = 0;
}
