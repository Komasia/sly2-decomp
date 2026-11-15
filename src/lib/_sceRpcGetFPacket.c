// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _sceRpcGetFPacket (libkernel sifrpc): next packet of the ring used for answers sent from interrupt handlers. */
typedef struct {
    int pid;                /* 0x00 */
    void *pkt_table;        /* 0x04 */
    int pkt_table_len;      /* 0x08 */
    int unused1, unused2;   /* 0x0C */
    char *rdata_table;      /* 0x14 */
    int rdata_table_len;    /* 0x18 */
    char *client_table;     /* 0x1C */
    int client_table_len;   /* 0x20 */
    int rdata_table_idx;    /* 0x24 */
} SifRpcData;

void *_sceRpcGetFPacket(SifRpcData *rpc)
{
    int i = rpc->rdata_table_idx % rpc->rdata_table_len;
    char *pkt = rpc->rdata_table + (i << 6);
    rpc->rdata_table_idx = i + 1;
    return pkt;
}
