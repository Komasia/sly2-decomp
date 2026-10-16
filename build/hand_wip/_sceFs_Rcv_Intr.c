// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 151/237. Header/size words are copied one 4-byte char-struct (W) at a time (lwl/lwr+swl/swr); big copies are int-aligned struct assignments (ldl runtime-align loop / unrolled). Jump table cases 2,11,12,23/25/26. Left: reg alloc (idx a1, case-11 copy regs), store order of D_002C4A78. */
typedef struct { char b[0x440]; } FsPkt;
typedef struct { int sema; int cmd; void *dst; int size; } RcvHdr;
typedef struct { char c[4]; } W;
typedef struct { int n1; int n2; char *dst1; char *dst2; char buf1[0x40]; char buf2[0x40]; } RdTail;
typedef struct { int b[0x51]; } Dirent;
typedef struct { int b[0x10]; } Stat;
typedef struct { int x0, x4, x8, idx; } SifCmdHdr;
extern int D_002C4A80;
extern int D_002C4A78;
extern int D_002C49F8[32];
extern FsPkt D_0044B300[];
void func_0023320C(void *, const void *, unsigned int);
void func_00234A50(int);

void _sceFs_Rcv_Intr(SifCmdHdr *cmd)
{
    RcvHdr h;
    struct DP { void *dst; unsigned int size; } d;
    char *dst, *udst;
    char *p;
    RdTail *rd;
    int idx, i, v;

    idx = 0;
    if (D_002C4A80)
        idx = cmd->idx;
    D_002C4A78 = idx;
    p = (char *)((unsigned int)&D_0044B300[idx] | 0x20000000);
    *(W *)&h.sema = *(W *)(p + 0);
    *(W *)&h.cmd = *(W *)(p + 4);
    *(W *)&h.dst = *(W *)(p + 8);
    *(W *)&h.size = *(W *)(p + 12);
    if (h.sema >= 0)
        func_0023320C(h.dst, p + 0x10, h.size);
    switch (h.cmd) {
    case 2:
        rd = (RdTail *)(p + 0x14);
        if (rd->n1 > 0) {
            dst = rd->dst1;
            udst = (char *)((unsigned int)dst | 0x20000000);
            for (i = 0; i < rd->n1; i++)
                dst[i] = udst[i] = rd->buf1[i];
        }
        if (rd->n2 > 0) {
            dst = rd->dst2;
            udst = (char *)((unsigned int)dst | 0x20000000);
            for (i = 0; i < rd->n2; i++)
                dst[i] = udst[i] = rd->buf2[i];
        }
        break;
    case 11:
        if (*(int *)h.dst > 0) {
            *(W *)&d.dst = *(W *)(p + 0x14);
            *(Dirent *)d.dst = *(Dirent *)(p + 0x18);
        }
        break;
    case 12:
        *(W *)&d.dst = *(W *)(p + 0x14);
        *(Stat *)d.dst = *(Stat *)(p + 0x18);
        break;
    case 23:
    case 25:
    case 26:
        *(W *)&d.dst = *(W *)(p + 0x14);
        *(W *)&d.size = *(W *)(p + 0x18);
        if (d.size > 0x400)
            d.size = 0x400;
        func_0023320C(d.dst, p + 0x1C, d.size);
        break;
    }
    if (h.sema < 0) {
        h.sema = -h.sema;
        v = h.sema;
        for (i = 0; i < 32; i++) {
            if (D_002C49F8[i] == v) {
                D_002C49F8[i] = -1;
                break;
            }
        }
        return;
    }
    func_00234A50(h.sema);
}
