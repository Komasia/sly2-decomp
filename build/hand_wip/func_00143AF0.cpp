struct CRef;
extern "C" void func_00129EC8(CRef *);
extern "C" void func_001291A8(CRef *, const CRef *);
struct CRef {
    int tagk; int tag;
    CRef() { tagk = -1; }
    CRef(int n, int k) { tag = n; tagk = k; }
    CRef(int k, int n, int) { tagk = k; tag = n; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { func_00129EC8(this); }
};
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct LO { char pad[0xC]; VTE *vt; char pad2[0x18 - 0x10]; void *p18; };
struct G;
extern "C" G D_003D4A60;
extern char D_002A4DB0[];
extern "C" {
void *func_00143410(void *p);
CRef func_00258200(void *p, const CRef &ref, G *pv);
CRef func_001D8B20(const CRef &ref, void *o, void *pv, int n);
}
static inline void Send(void *pv, CRef ref) { func_00258200(pv, ref, &D_003D4A60); }
extern "C" void *func_00143AF0(LO *p, int x)
{
    void *pv = func_00143410(p->p18);
    if (pv) {
        CRef a(x, 0x15);
        Send(pv, a);
    }
    VTE *e = &p->vt[103];
    CRef ret = func_001D8B20(CRef(0x15, -1, 0), e->pfn((char *)p + e->d), D_002A4DB0, 0);
    return pv;
}
