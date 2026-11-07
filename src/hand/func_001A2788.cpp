typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct FRAME { int a[4]; FRAME(); ~FRAME(); };
struct MSG { int cb; int nKind; };
struct HIT { qword pos; char pad[0x5F0]; };
struct O { char pad[0x1098]; float x1098; float x109C; };
struct L { char pad[0xE0]; int xE0; };
extern "C" {
extern qword D_002A2DD0;
qword func_001A62E8(void *p);
void *PvAllocStackImpl(MSG *pmsg) asm("PvAllocStackImpl__Fi");
int CsoeCollect(L *pl, void *pfn, int n, void *pv) asm("CsoeCollect__FP3ALOPvN21");
int CClipSegmentEntries(qword a, qword b, int n, void *pv, int c, HIT *phit) asm("CClipSegmentEntries__FG9VU_VECTORT0iP3LSGiT3");
void func_00229D60(void);
int FWaterSurfaceUnder(O *po, L *pl, qword *pv) asm("FWaterSurfaceUnder__FP5ACTORP3ALOP6VECTOR");
}
// name: SafeHouse port (FWaterSurfaceUnder)
int FWaterSurfaceUnder(O *po, L *pl, qword *pv)
{
    U off, b, a;
    HIT hit;
    off.q = D_002A2DD0;
    {
        qword p = func_001A62E8(po);
        qword d;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p), "j"(off.q));
        a.q = d;
        b.q = d;
    }
    a.f[2] += po->x109C;
    b.f[2] += po->x1098;
    FRAME frame;
    MSG msg;
    MSG *pmsg = &msg;
    pmsg->cb = pl->xE0 * 4;
    pmsg->nKind = 0x10;
    void *pbuf = PvAllocStackImpl(pmsg);
    int n = CsoeCollect(pl, (void *)func_00229D60, 0, pbuf);
    if (!CClipSegmentEntries(a.q, b.q, n, pbuf, 0x10, &hit))
        return 0;
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(hit.pos), "j"(off.q));
    *pv = r;
    return 1;
}
