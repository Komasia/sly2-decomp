/* Appends cAdd ints to the array (grown by doubling, at least 32, on the stack heap; the old contents copied). */
struct ALLOCREQ { int cb; int cbAlign; };
struct AN { int f0; int cMax; int c; int *a; };   /* a growable int array on the stack heap */
void *PvAllocStackImpl__Fi(struct ALLOCREQ *);
void CopyAb(void *, void *, int) asm("CopyAb__FPvT0Ui");
static inline int Max(int a, int b) { return a < b ? b : a; }
void func_0013F8A8(struct AN *pan, int cAdd, int *aAdd) {
    if (pan->cMax < pan->c + cAdd) {
        int cMax = pan->cMax;
        struct ALLOCREQ req;
        int *a;
        do {
            cMax = Max(cMax * 2, 32);
        } while (cMax < pan->c + cAdd);
        req.cb = cMax * 4;
        req.cbAlign = 0x10;
        a = PvAllocStackImpl__Fi(&req);
        CopyAb(a, pan->a, pan->c * 4);
        pan->cMax = cMax;
        pan->a = a;
    }
    CopyAb(pan->a + pan->c, aAdd, cAdd * 4);
    pan->c += cAdd;
}
