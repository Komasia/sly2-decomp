/* near miss: only missing target's 'addiu v1,zero,1' (re-materialised pid==1) in the pid==1 branch; rest identical. */
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct {
    int pad[4];
    unsigned int rec_id;  /* 0x10 */
    void *pkt_addr;       /* 0x14 */
    int pid;              /* 0x18 */
    int pad2[9];
} Pkt;
typedef struct {
    int pid;      /* 0x0 */
    Pkt *table;   /* 0x4 */
    int len;      /* 0x8 */
} RpcData;
void func_00239450(void);
int func_002394A0(void);
void *func_00236C28(RpcData *rd)
{
    Pkt *p;
    int i, len;
    func_00239450();
    len = rd->len;
    p = rd->table;
    for (i = 0; i < len; i++, p++) {
        if (!(p->rec_id & 1)) {
            int pid;
            p->rec_id = (i << 16) | 5;
            pid = ++rd->pid;
            if (pid == 1)
                rd->pid++;
            p->pkt_addr = p;
            p->pid = pid;
            func_002394A0();
            return p;
        }
    }
    func_002394A0();
    return 0;
}
