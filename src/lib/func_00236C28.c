/* _rpc_get_packet (libkernel sifrpc): take a free packet from the RPC packet table, mark it in use and give it
   the next rpc id. Returns 0 if all packets are busy. */
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    int sifcmd[4];        /* 0x00 SifCmdHeader */
    unsigned int rec_id;  /* 0x10 (slot << 16) | flags; bit 0 = in use */
    void *pkt_addr;       /* 0x14 */
    int rpc_id;           /* 0x18 */
    int pad2[9];
} SifRpcPkt;
typedef struct {
    int pid;                /* 0x0 last rpc id handed out */
    SifRpcPkt *pkt_table;   /* 0x4 */
    int pkt_table_len;      /* 0x8 */
} SifRpcData;
void DIntr(void);
int EIntr(void);
void *func_00236C28(SifRpcData *rd)
{
    SifRpcPkt *p;
    int i, len;
    DIntr();
    len = rd->pkt_table_len;
    p = rd->pkt_table;
    for (i = 0; i < len; i++, p++) {
        if (!(p->rec_id & 1)) {
            int pid;
            p->rec_id = (i << 16) | 5;
            if (++rd->pid == 1) {
                rd->pid++;
                pid = 1;
            } else {
                pid = rd->pid;
            }
            p->pkt_addr = p;
            p->rpc_id = pid;
            EIntr();
            return p;
        }
    }
    EIntr();
    return 0;
}
