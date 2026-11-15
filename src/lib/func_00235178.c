// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
int DIntr(void);
int EIntr(void);
int _EnableIntc(int);
// name: libkernel EnableIntc (DIntr / _EnableIntc / EIntr wrapper; suggested by l1)
int EnableIntc(int ch)
{
    int st;
    int r;
    __asm__ volatile("mfc0 %0, $12" : "=r"(st));
    st &= 0x10000;
    if (st) DIntr();
    r = _EnableIntc(ch);
    __asm__ volatile("sync");
    if (st) EIntr();
    return r;
}
