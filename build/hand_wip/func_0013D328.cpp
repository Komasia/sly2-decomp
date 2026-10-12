struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(int tagk, int n) { m_tagk = tagk; m_tag = n; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    void Decref();
};
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
struct S { char pad[0x194]; void *f194; };
struct G;
extern "C" {
extern G D_003D4A60;
void func_0013C560(void *, int);
void *func_0013D1A8(S *);
CRef func_00258200(void *, CRef *, G *);
void func_0013CF38(S *, int);
}
static inline void Set(void *pv, CRef r) { func_00258200(pv, &r, &D_003D4A60); }
extern "C" void func_0013D328(S *p, int n)
{
    if (p->f194) func_0013C560(p->f194, 0);
    FRAME frame;
    {
        CRef ref(0x15, n);
        Set(func_0013D1A8(p), ref);
    }
    if (n != -1) func_0013CF38(p, 0);
}
