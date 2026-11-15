// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _sceRpcGetFPacket2 (libkernel sifrpc): the client-table packet slot `rid`, or the next ring packet if rid is
   out of range. */
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
void *_sceRpcGetFPacket(SifRpcData *rpc);

void *_sceRpcGetFPacket2(SifRpcData *rpc, int rid)
{
    if (rid < 0 || rid >= rpc->client_table_len) return _sceRpcGetFPacket(rpc);
    return rpc->client_table + (rid << 6);
}
