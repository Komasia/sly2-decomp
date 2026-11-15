// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* InvalidDCache (libkernel): invalidate the data-cache lines covering [start, end] without writing them back. */
void DIntr(void);
void _sceIDC(unsigned int, unsigned int);
void EIntr(void);
void func_00235078(unsigned int start, unsigned int end)
{
    int intr;
    __asm__ volatile("mfc0 %0, $12" : "=r"(intr));
    intr &= 0x10000;     /* Status.EIE */
    if (intr) DIntr();
    _sceIDC(start & ~0x3F, end & ~0x3F)   /* whole 64-byte lines */;
    if (intr) EIntr();
}
