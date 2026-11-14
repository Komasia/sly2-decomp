// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
int DIntr(void);
int EIntr(void);
int _EnableDmac(int);
int func_00235248(int ch)
{
    int st;
    int r;
    __asm__ volatile("mfc0 %0, $12" : "=r"(st));
    st &= 0x10000;
    if (st) DIntr();
    r = _EnableDmac(ch);
    __asm__ volatile("sync");
    if (st) EIntr();
    return r;
}
