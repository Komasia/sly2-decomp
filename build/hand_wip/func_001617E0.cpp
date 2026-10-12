// 14% diff: slots right; target keeps %hi(D_003D4A60) in s0 across copy ctor and doesn't CSE &copy.
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(int n) { m_tagk = 0x15; m_tag = n; }
    CRef(const CRef &ref);
    ~CRef() { Decref(); }
    void Decref();
};
struct O;
extern char D_003D4A60[];
extern "C" CRef func_00258200(O *, const CRef &, void *);
static inline void SetPv(O *pv, CRef r, void *pvKey) { func_00258200(pv, r, pvKey); }
struct G { char pad[0x3B20]; O *f3b20; };
extern G D_003DD490;
extern "C" void func_00161868(G *pg);
extern "C" void func_001617E0(void *pv, int n)
{
    G *pg = &D_003DD490;
    {
        O *po = pg->f3b20;
        CRef ref(n);
        SetPv(po, ref, D_003D4A60);
    }
    func_00161868(pg);
}
