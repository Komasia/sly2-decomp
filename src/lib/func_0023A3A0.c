// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* StartTimerCounter (libkernel): thread-safe wrapper, iStartTimerCounter with interrupts disabled. */
int DIntr(void);
int iStartTimerCounter(int);
int EIntr(void);

int func_0023A3A0(int id)
{
    int intr = DIntr();
    int ret = iStartTimerCounter(id);
    if (intr) EIntr();
    return ret;
}
