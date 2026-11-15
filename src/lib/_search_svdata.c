// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _search_svdata (libkernel sifrpc): find the registered RPC server with id `sid` on any active queue. */
typedef struct SifRpcServerData { int sid; int pad[13]; struct SifRpcServerData *link; /* 0x38 */ } SifRpcServerData;
typedef struct SifRpcDataQueue {
    int thread_id, active;              /* 0x00 */
    SifRpcServerData *link;             /* 0x08 servers on this queue */
    int start, end;                     /* 0x0C */
    struct SifRpcDataQueue *next;       /* 0x14 */
} SifRpcDataQueue;
typedef struct { int pad[10]; SifRpcDataQueue *active_queue; /* 0x28 */ } SifRpcData;

SifRpcServerData *_search_svdata(int sid, SifRpcData *rpc)
{
    SifRpcDataQueue *queue;
    SifRpcServerData *server;
    for (queue = rpc->active_queue; queue; queue = queue->next) {
        for (server = queue->link; server; server = server->link)
            if (server->sid == sid) return server;
    }
    return 0;
}
