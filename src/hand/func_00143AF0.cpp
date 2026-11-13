struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
extern "C" void func_001291A8(CRef *, const CRef *);
struct CRef {
    int tagk; int tag;
    CRef() { tagk = -1; }
    CRef(int n, int k) { tag = n; tagk = k; }
    CRef(int k, int n, int) { tagk = k; tag = n; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { Decref(this); }
};
struct CRefRaw { int tagk; int tag; };  /* same layout, no ctor/dtor */
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct LO { char pad[0xC]; VTE *vt; char pad2[0x18 - 0x10]; void *p18; };
struct G;
extern "C" G D_003D4A60;
extern char D_002A4DB0[];
extern "C" {
void *AkeyStandHeldBy(void *p) asm("AkeyStandHeldBy__Fi");
CRef func_00258200(void *p, const CRef &ref, G *pv);
CRef SetProgressPoCurrent(const CRef &ref, void *o, void *pv, int n) asm("SetProgressPoCurrent__FP4CRefPci");
}
/* Same SetPv form as SetStandBooty: the unused dummy param makes gcc set up %hi(D_003D4A60)
   before the copy (lui in the copy-ctor jal slot). The copy is made in a raw struct with explicit
   copy/dtor calls: an inlined ~CRef would put &arg in a pseudo that gcse PRE then shares with
   the second CRef temp at the same stack slot. */
static inline void SetPv(void *pv, const CRef &r, void *)
{
    CRefRaw arg;
    func_001291A8((CRef *)&arg, &r);
    {
        const CRef &ret = func_00258200(pv, *(CRef *)&arg, &D_003D4A60);
    }
    Decref((CRef *)&arg);
}
// name: SafeHouse port (AkeyReturnBooty)
extern "C" void *AkeyReturnBooty__FP5ACTORi(LO *p, int x)
{
    void *pv = AkeyStandHeldBy(p->p18);
    if (pv) {
        CRef a(x, 0x15);
        SetPv(pv, a, &D_003D4A60);
    }
    VTE *e = &p->vt[103];
    CRef ret = SetProgressPoCurrent(CRef(0x15, -1, 0), e->pfn((char *)p + e->d), D_002A4DB0, 0);
    return pv;
}
