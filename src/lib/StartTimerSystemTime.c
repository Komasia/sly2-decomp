// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
int DIntr(void);
int EIntr(void);
void func_00239AC0(unsigned int);
int iGetTimerSystemTime(void);
void SetNextComp(int);
int StartTimerSystemTime(void)
{
    int st = DIntr();
    unsigned int mode = *(volatile unsigned int *)0x10001010;
    if (mode & 0x80) {
        if (st) EIntr();
        return 1;
    }
    func_00239AC0((mode & 0xFFFFF3FF) | 0x80);
    SetNextComp(iGetTimerSystemTime());
    if (st) EIntr();
    return 0;
}
