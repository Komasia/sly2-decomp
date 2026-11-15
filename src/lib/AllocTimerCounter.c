// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* AllocTimerCounter (libkernel): thread-safe wrapper, iAllocTimerCounter with interrupts disabled.
   Built with 2.95.3-114's Sony slot layout (s0@0, s1@0x10, ra@0x20) and the sq->sd/lq->ld assembler macro. */
int DIntr(void);
int EIntr(void);
int iAllocTimerCounter(void);

int AllocTimerCounter(void)
{
    int intr = DIntr();
    int id = iAllocTimerCounter();
    if (intr) EIntr();
    return id;
}
