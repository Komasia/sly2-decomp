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
extern "C" { void func_00141968(void *p, qword, float, float); CRef func_0010A790(void *p, int c, void *aref); }
CRef func_0010A790(void *p, int c, void *aref)
{
    int ak[3] = {0x2, 0x1, 0x1};
    union { qword q; } v0;
    float v1;
    float v2;
    CRef ref = func_00201360(3, aref, ak, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(0x24);
    func_00141968(p, v0.q, v1, v2);
    return ref;
}
