// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* _request_bind (libkernel sifrpc): SIF_CMD_RPC_BIND handler: the IOP wants to bind to one of our RPC servers.
   Look the server up by sid and answer with an RPC end packet; if the SIF queue is full, retry from an alarm. */
typedef struct {
    SifCmdHeader sifcmd;    /* 0x00 */
    unsigned int rec_id;    /* 0x10 */
    int pkt_addr;           /* 0x14 */
    int rpc_id;             /* 0x18 */
    int client;             /* 0x1C */
    int cid;                /* 0x20 bind request: sid; end packet: the command that ended */
    int server;             /* 0x24 */
    int buff;               /* 0x28 */
    int cbuff;              /* 0x2C */
    int pad[4];
} SifRpcPkt;
typedef struct { int sid; int func; int buff; } SifRpcServerData;
SifRpcPkt *_sceRpcGetFPacket(void *data);
SifRpcServerData *_search_svdata(int sid, void *data);
unsigned int isceSifSendCmd(unsigned int cid, void *pkt, int size, int src, int dst, int n);
int iSetTimerAlarm(unsigned short t, void (*h)(void *), void *arg);
void _alarm_bind(void *);

void _request_bind(SifRpcPkt *bind, void *data)
{
    SifRpcPkt *rend;
    SifRpcServerData *server;
    rend = _sceRpcGetFPacket(data);
    {
        int pkt_addr = bind->pkt_addr, client = bind->client;
        rend->client = client;
        rend->pkt_addr = pkt_addr;
    }
    rend->cid = SIF_CMD_RPC_BIND;
    server = _search_svdata(bind->cid, data);
    if (server == 0) {
        rend->server = 0;
        rend->buff = 0;
    } else {
        rend->server = (int)server;
        rend->buff = server->buff;
    }
    if (isceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_RPC_PACKET_SIZE, 0, 0, 0) == 0)
        iSetTimerAlarm(0x800, _alarm_bind, rend);
}
