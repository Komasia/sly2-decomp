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
extern "C" { void func_001F82B8(void *p, int, void *); CRef func_00101608(void *p, int c, void *aref); }
CRef func_00101608(void *p, int c, void *aref)
{
    int ak[2] = {0x104d, 0xa};
    union { qword q; } v1;
    int v0;
    CRef ref = func_00201360(2, aref, ak, &v0, &v1);
    ref.Decref();
    ref.InitTag(0x24);
    func_001F82B8(p, v0, &v1);
    return ref;
}
