// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -fno-strict-aliasing -G0
// SLY2_ASM: gnu-reorder-db
/* _request_call (libkernel sifrpc): SIF_CMD_RPC_CALL handler: queue the call on the server's data queue and
   wake the server thread if it is idle (sceSifRpcLoop picks it up). */
typedef struct SifRpcDataQueue {
    int thread_id;                      /* 0x00 */
    int active;                         /* 0x04 */
    struct SifRpcServerData *link;      /* 0x08 servers on this queue */
    struct SifRpcServerData *start;     /* 0x0C pending calls */
    struct SifRpcServerData *end;       /* 0x10 */
} SifRpcDataQueue;
typedef struct SifRpcServerData {
    int sid;                            /* 0x00 */
    int func;                           /* 0x04 */
    int buff;                           /* 0x08 */
    int size;                           /* 0x0C */
    int cfunc;                          /* 0x10 */
    int cbuff;                          /* 0x14 */
    int size2;                          /* 0x18 */
    int client;                         /* 0x1C */
    int pkt_addr;                       /* 0x20 */
    int rpc_number;                     /* 0x24 */
    int receive;                        /* 0x28 */
    int rsize;                          /* 0x2C */
    int rmode;                          /* 0x30 */
    int rid;                            /* 0x34 */
    int link;                           /* 0x38 */
    struct SifRpcServerData *next;      /* 0x3C next pending call */
    SifRpcDataQueue *base;              /* 0x40 */
} SifRpcServerData;
typedef struct {
    int sifcmd[4];                      /* 0x00 SifCmdHeader */
    int rec_id;                         /* 0x10 */
    int pkt_addr;                       /* 0x14 */
    int rpc_id;                         /* 0x18 */
    int client;                         /* 0x1C */
    int rpc_number;                     /* 0x20 */
    int send_size;                      /* 0x24 */
    int receive;                        /* 0x28 */
    int rec_size;                       /* 0x2C */
    int rmode;                          /* 0x30 */
    SifRpcServerData *server;           /* 0x34 */
} SifRpcCallPkt;
void iWakeupThread(int);

void _request_call(SifRpcCallPkt *call)
{
    SifRpcServerData *sd = call->server;
    SifRpcDataQueue *queue = sd->base;
    if (queue->start == 0)
        queue->start = sd;
    else
        queue->end->next = sd;
    queue->end = sd;
    {
        int pkt_addr = call->pkt_addr, client = call->client;
        sd->pkt_addr = pkt_addr;
        sd->client = client;
    }
    sd->rpc_number = call->rpc_number;
    sd->size = call->send_size;
    sd->receive = call->receive;
    sd->rsize = call->rec_size;
    sd->rmode = call->rmode;
    sd->rid = call->rec_id;
    if (queue->thread_id >= 0 && queue->active == 0)
        iWakeupThread(queue->thread_id);
}
