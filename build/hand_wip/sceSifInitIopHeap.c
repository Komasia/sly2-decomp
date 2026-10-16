// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
// (Claude agent) near miss: fails to assemble: reorg fills the 1-insn delay loop slot from its own target (problematic short loop); gnu-reorder gets loop right but no bgezl
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
