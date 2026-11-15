// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* DisableIntc (libkernel): disable an INTC interrupt cause, with interrupts held off around the syscall. */
int DIntr(void);
int EIntr(void);
int _DisableIntc(int);
int func_00235110(int ch)
{
    int intr;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(intr));
    intr &= 0x10000;     /* Status.EIE */
    if (intr) DIntr();
    ret = _DisableIntc(ch);
    __asm__ volatile("sync");
    if (intr) EIntr();
    return ret;
}
