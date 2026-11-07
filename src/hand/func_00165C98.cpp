struct ALLOCREQ { int cb; int nKind; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
struct X { char pad[0x94]; int f94; char pad2[0xFC - 0x98]; int fFC; };
struct G { char pad[0x3AFC]; int c; };
extern G g_sw;
extern "C" void *PvAllocStackClearImpl(ALLOCREQ *preq) asm("PvAllocStackClearImpl__Fi");
extern "C" int func_0015E9C8(G *pg, int kind, int n, int m, int c, void **apv);
extern "C" void VisitTask(X *px, int *pc, void *pv, int a, int b) asm("VisitTask__FP4TASKPiPvii");
extern "C" void func_00165C98(int *pc, void **ppv)
{
    ALLOCREQ req;
    G *pg = &g_sw;
    *pc = 0;
    req.cb = pg->c * 4;
    req.nKind = 0x10;
    *ppv = PvAllocStackClearImpl(&req);
    FRAME fr;
    req.cb = pg->c * 4;
    req.nKind = 0x10;
    X **apx = (X **)PvAllocStackClearImpl(&req);
    int c = func_0015E9C8(pg, 5, 0x85, 0, pg->c, (void **)apx);
    int i;
    for (i = 0; i < c; i++)
        apx[i]->fFC = 0;
    for (int j = 0; j < c; j++) {
        if (!apx[j]->f94)
            VisitTask(apx[j], pc, *ppv, 0, 0);
    }
}
