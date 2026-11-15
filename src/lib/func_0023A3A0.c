// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* StartTimerCounter (libkernel): thread-safe wrapper, iStartTimerCounter with interrupts disabled. */
int DIntr(void);
int iStartTimerCounter(int);
int EIntr(void);

// name: libkernel StartTimerCounter (DIntr / iStartTimerCounter / EIntr like AllocTimerCounter; suggested by l1)
int StartTimerCounter(int id)
{
    int intr = DIntr();
    int ret = iStartTimerCounter(id);
    if (intr) EIntr();
    return ret;
}
