// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
int DIntr(void);
int iSetTimerHandler(int, int, int, int);
int EIntr(void);
int SetTimerHandler(int id, int a, int b, int c)
{
    int st = DIntr();
    int r = iSetTimerHandler(id, a, b, c);
    if (st) EIntr();
    return r;
}
