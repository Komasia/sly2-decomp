// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// MATCH with 2.95.3-114 (Sony slot layout s0@0,s1@0x10,ra@0x20) + the sq->sd/lq->ld assembler macro (Claude agent).
int DIntr(void);
int iAllocTimerCounter(void);
int EIntr(void);
int AllocTimerCounter(void)
{
    int st = DIntr();
    int r = iAllocTimerCounter();
    if (st) EIntr();
    return r;
}
