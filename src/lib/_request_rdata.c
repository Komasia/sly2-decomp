// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* _request_rdata (libkernel sifrpc): SIF_CMD_RPC_RDATA handler: the IOP asks us to send it `size` bytes from
   `src`. The data goes along with an RPC end packet (retried from an alarm if the SIF queue is full). */
typedef struct {
    SifCmdHeader sifcmd;    /* 0x00 */
    unsigned int rec_id;    /* 0x10 bit 2: answer in the client packet slot in bits 16.. */
    int pkt_addr;           /* 0x14 */
    int rpc_id;             /* 0x18 */
    int client;             /* 0x1C */
    int src;                /* 0x20 */
    int dest;               /* 0x24 */
    int size;               /* 0x28 */
    int pad[5];
} SifRpcRdataPkt;
typedef struct {
    SifCmdHeader sifcmd;    /* 0x00 */
    unsigned int rec_id;    /* 0x10 */
    int pkt_addr;           /* 0x14 */
    int rpc_id;             /* 0x18 */
    int client;             /* 0x1C */
    int cid;                /* 0x20 command that ended */
    int src;                /* 0x24 */
    int dest;               /* 0x28 */
    int size;               /* 0x2C */
    int pad[4];
} SifRpcEndPkt;
SifRpcEndPkt *_sceRpcGetFPacket(void *data);
SifRpcEndPkt *_sceRpcGetFPacket2(void *data, int n);
unsigned int isceSifSendCmd(unsigned int cid, void *pkt, int size, int src, int dst, int n);
int iSetTimerAlarm(unsigned short t, void (*h)(void *), void *arg);
void _alarm_rdata(void *);

void _request_rdata(SifRpcRdataPkt *rdata, void *data)
{
    SifRpcEndPkt *rend;
    if (rdata->rec_id & 4)
        rend = _sceRpcGetFPacket2(data, rdata->rec_id >> 16);
    else
        rend = _sceRpcGetFPacket(data);
    {
        int pkt_addr = rdata->pkt_addr, client = rdata->client;
        rend->pkt_addr = pkt_addr;
        rend->client = client;
    }
    rend->cid = SIF_CMD_RPC_RDATA;
    rend->src = rdata->src;
    rend->dest = rdata->dest;
    rend->size = rdata->size;
    if (isceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_RPC_PACKET_SIZE, rdata->src, rdata->dest, rdata->size) == 0)
        iSetTimerAlarm(0x800, _alarm_rdata, rend);
}
