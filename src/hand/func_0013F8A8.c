struct ALLOCREQ { int cb; int cbAlign; };
struct A { int f0; int cMax; int c; int *a; };
void *PvAllocStackImpl__Fi(struct ALLOCREQ *);
void CopyAb(void *, void *, int) asm("CopyAb__FPvT0Ui");
static inline int Max(int a, int b) { return a < b ? b : a; }
void func_0013F8A8(struct A *pa, int cAdd, int *aAdd) {
    if (pa->cMax < pa->c + cAdd) {
        int cMax = pa->cMax;
        struct ALLOCREQ req;
        int *a;
        do {
            cMax = Max(cMax * 2, 32);
        } while (cMax < pa->c + cAdd);
        req.cb = cMax * 4;
        req.cbAlign = 0x10;
        a = PvAllocStackImpl__Fi(&req);
        CopyAb(a, pa->a, pa->c * 4);
        pa->cMax = cMax;
        pa->a = a;
    }
    CopyAb(pa->a + pa->c, aAdd, cAdd * 4);
    pa->c += cAdd;
}
