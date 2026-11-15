struct ALLOCREQ { int cb; int nKind; };
class CBinaryInputStream {
public:
    int U8Read();
    int U16Read();
    int S16Read();
};
// LoadIdxTabFromBrx: load an index table: c rows of {two RGBA16 colours (AdjustRgba16), a byte} entries, then a list
// of indices.
struct IDXE { short rgba0; short rgba1; char b; char pad; };
struct IDXROW { int c; IDXE *a; };
struct IDXTAB { int c; IDXROW *a; int *ai; };
extern "C" void *PvAllocStackClearImpl(ALLOCREQ *preq) asm("PvAllocStackClearImpl__Fi");
extern "C" void AdjustRgba16(short *ps) asm("AdjustRgba16__FPUs");
static inline void *PvAllocReq(ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocStackClearImpl(preq);
}
// name: SafeHouse port (LoadIdxTabFromBrx)
extern "C" IDXTAB *LoadIdxTabFromBrx__FP18CBinaryInputStreamT0(void *pv, CBinaryInputStream *pbis)
{
    IDXTAB *pt = 0;
    int c = pbis->U16Read();
    if (c) {
        ALLOCREQ req;
        pt = (IDXTAB *)PvAllocReq(&req, sizeof(IDXTAB), 0x10);
        pt->c = c;
        pt->a = (IDXROW *)PvAllocReq(&req, c * sizeof(IDXROW), 0x10);
        for (int i = 0; i < pt->c; i++) {
            IDXROW *pe = &pt->a[i];
            int n = pbis->U16Read();
            pe->a = (IDXE *)PvAllocReq(&req, n * sizeof(IDXE), 0x10);
            for (int j = 0; j < n; j++) {
                IDXE *p6 = &pe->a[j];
                short *pb = &p6->rgba1;
                p6->rgba0 = pbis->U16Read();
                p6->rgba1 = pbis->U16Read();
                p6->b = pbis->U8Read();
                AdjustRgba16(&p6->rgba0);
                AdjustRgba16(pb);
            }
        }
        int m = pbis->U16Read();
        pt->ai = (int *)PvAllocReq(&req, m * 4, 0x10);
        for (int k = 0; k < m; k++)
            pt->ai[k] = pbis->S16Read();
    }
    return pt;
}
