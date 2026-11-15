// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* SIF_CMD_SET_SREG handler (libkernel sifcmd): the IOP sets one of our software registers. */
typedef struct { int sifcmd[4]; int reg; int val; } SifSetSregPkt;
typedef struct { int pad[7]; int *sreg; /* 0x1C */ } SifCmdData;
void func_0023AA98(SifSetSregPkt *pkt, SifCmdData *cmd)
{
    cmd->sreg[pkt->reg] = pkt->val;
}
