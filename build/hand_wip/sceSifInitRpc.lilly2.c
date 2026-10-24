// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
typedef struct {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    void *rdata_table;
    int rdata_table_len;
    void *client_table;
    int client_table_len;
    int client_table_idx;
} RpcData;
typedef struct { int x0, x4, x8, xc; } Cmd;
extern int D_002C49F0;
extern unsigned char D_00448E00[];
extern unsigned char D_00449600[];
extern unsigned char D_00449E00[];
extern RpcData D_0044A600;
void DIntr(void);
void func_002394A0(void);
void sceSifInitCmd(void);
void sceSifAddCmdHandler(unsigned int cid, void (*h)(void *, void *), void *data);
int func_00234E30(unsigned int reg);
void func_00234E20(unsigned int reg, int val);
unsigned int sceSifSendCmd(unsigned int cid, void *pkt, int size, void *src, void *dst, int n);
int func_0023AAC8(int);
void _request_end(void *, void *);
void _request_bind(void *, void *);
void _request_call(void *, void *);
void _request_rdata(void *, void *);
static inline void *U(void *p) { return (void *)((unsigned int)p | 0x20000000); }
void sceSifInitRpc(unsigned int mode)
{
    Cmd *cmd;
    DIntr();
    if (D_002C49F0) {
        func_002394A0();
        return;
    }
    D_002C49F0 = 1;
    func_002394A0();
    sceSifInitCmd();
    DIntr();
    {
    void *b = (void *)((unsigned int)D_00449600 | 0x20000000);
    void *c = (void *)((unsigned int)D_00449E00 | 0x20000000);
    void *a = (void *)((unsigned int)D_00448E00 | 0x20000000);
    D_0044A600.pkt_table = a;
    D_0044A600.pkt_table_len = 32;
    D_0044A600.rdata_table_len = 32;
    D_0044A600.client_table_len = 32;
    D_0044A600.pid = 1;
    D_0044A600.unused2 = 0;
    D_0044A600.rdata_table = b;
    D_0044A600.unused1 = 0;
    D_0044A600.client_table_idx = 0;
    D_0044A600.client_table = c;
    }
    sceSifAddCmdHandler(0x80000008, _request_end, &D_0044A600);
    sceSifAddCmdHandler(0x80000009, _request_bind, &D_0044A600);
    sceSifAddCmdHandler(0x8000000A, _request_call, &D_0044A600);
    sceSifAddCmdHandler(0x8000000C, _request_rdata, &D_0044A600);
    func_002394A0();
    if (func_00234E30(0x80000002) != 0)
        return;
    cmd = (Cmd *)(D_00448E00 + 0x40);
    cmd->xc = 1;
    sceSifSendCmd(0x80000002, cmd, 16, 0, 0, 0);
    while (func_0023AAC8(0) == 0)
        ;
    func_00234E20(0x80000002, 1);
}

// WIP aligned 4 (7/103): uncached addrs in block locals (a,b,c assigned b,c,a) + store-order hill-climb. Left: lui v1/v0 for pkt-hi and sw 0x1C scheduling. (Claude agent)
// lilly1 (T1554): same body as v2 (aligned 4, 7/103 raw). Root cause of what is left (sched1 dump, -fsched-verbose-5):
//  target has hi(pkt) in v1 = the 0x20000000 constant (v0) is born BEFORE lo(pkt) in the sched1 order, so the two
//  live ranges overlap. Ours schedules lui(0x2000) after lo(pkt): lo_sum has INSN_REG_WEIGHT 0 (its hi dies there), the
//  const has +1, equal priority 18 -> lo wins. Needs prio(const) 19 or a 2nd use of hi(pkt); no source form found.
// Searched: 14-worker hill-climb (3 pointers as locals/inline x all statement orders x void*/unsigned pointer-field
//  types, ~30 min): nothing under 7 raw / aligned 4 except (10, 5) variants with the same lui diff.
// lilly2 (T1564): lilly1 + -fstrict-aliasing; still aligned 4 (7/103 raw). ~1500 random distinct-pointer-type assignments for the RpcData
//  fields under -fstrict-aliasing also plateau at (aligned 4, 7 raw): the store-order part is NOT the lever, only hi(pkt) v1/v0 (see notes/23C000.md T1564).
