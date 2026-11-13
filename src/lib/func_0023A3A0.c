// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
int DIntr(void);
int iStartTimerCounter(int);
int EIntr(void);
int func_0023A3A0(int id)
{
    int st = DIntr();
    int r = iStartTimerCounter(id);
    if (st) EIntr();
    return r;
}
