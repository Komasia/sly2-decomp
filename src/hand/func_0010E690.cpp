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
extern "C" { void func_001F8AD8(void *p, int a, int b, void *ps); CRef func_0010E690(void *p, int c, void *aref); }
struct BIG { qword aq[4]; };
CRef func_0010E690(void *p, int c, void *aref)
{
    int ak[3] = {0x100D, 5, 4};
    BIG s;
    int a, b;
    CRef ref = func_00201360(3, aref, ak, &a, &b, &s);
    ref.Decref();
    ref.InitTag(0x24);
    func_001F8AD8(p, a, b, &s);
    return ref;
}
