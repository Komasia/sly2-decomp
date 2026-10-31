/* sceSifCheckStatRpc (libkernl sifrpc): is the RPC call made through cd still in flight on the IOP? It is while the
 * packet the call used is allocated and still carries the call's id. (Field names after ps2sdk's sifrpc.) */

typedef struct SifRpcPktHeader {
    /* 0x00 */ char sifcmd[0x10];      /* SIF command header */
    /* 0x10 */ int rec_id;             /* bit 0: packet allocated */
    /* 0x14 */ void *pkt_addr;
    /* 0x18 */ int rpc_id;
} SifRpcPktHeader;

typedef struct sceSifRpcData {
    /* 0x00 */ SifRpcPktHeader *pkt;   /* packet of the last call */
    /* 0x04 */ int rpc_id;
    /* 0x08 */ int sema_id;
    /* 0x0c */ unsigned int mode;
} sceSifRpcData;

#define PACKET_F_ALLOC 1

int sceSifCheckStatRpc(sceSifRpcData *cd)
{
    SifRpcPktHeader *pkt = cd->pkt;

    if (pkt == 0 || cd->rpc_id != pkt->rpc_id || !(pkt->rec_id & PACKET_F_ALLOC))
        return 0;
    return 1;
}
