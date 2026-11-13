// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
void DIntr(void);
void _sceSDC(unsigned int, unsigned int);
void EIntr(void);
void func_00234F48(unsigned int start, unsigned int end)
{
    int s;
    __asm__ volatile("mfc0 %0, $12" : "=r"(s));
    s &= 0x10000;
    if (s) DIntr();
    _sceSDC(start & ~0x3F, end & ~0x3F);
    if (s) EIntr();
}
