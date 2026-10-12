typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};
extern "C" CRef func_00201360(int c, void *aref, int *ak, ...);
extern "C" { void func_001D4B48(void *p, int n, void *pu, float g); CRef func_001104F0(void *p, int c, void *aref); }
CRef func_001104F0(void *p, int c, void *aref)
{
    int ak[3] = {0x12, 0x11, 0x10};
    union { qword q; } u;
    int n;
    float g;
    CRef ref = func_00201360(3, aref, ak, &n, &g, &u);
    ref.Decref();
    ref.InitTag(0x24);
    func_001D4B48(p, n, &u, g);
    return ref;
}
