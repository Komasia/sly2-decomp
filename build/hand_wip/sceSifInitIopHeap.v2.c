// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// (Claude agent) 2.9-991111: 3 diffs - tail 'D_002C4A94 = 0; return 0;': target lui v0/sw/daddu v0, ours sets v0=0 first (volatile/return-assign no help).
typedef struct { char p[0x24]; int server; } RpcCD;
extern int D_002C4A94;
extern RpcCD D_0044BE80;
int func_002370A8(RpcCD *, unsigned int, int);
int sceSifInitIopHeap(void)
{
    int i;
    for (;;) {
        if (func_002370A8(&D_0044BE80, 0x80000003, 0) < 0)
            return -1;
        if (D_0044BE80.server != 0)
            break;
        i = 0x100000;
        while (i--)
            ;
    }
    D_002C4A94 = 0;
    return 0;
}
