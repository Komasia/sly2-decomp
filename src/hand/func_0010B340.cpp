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
extern "C" { void func_0019EAA0(void *p, qword a, qword b); CRef func_0010B340(void *p, int c, void *aref); }
CRef func_0010B340(void *p, int c, void *aref)
{
    int ak[2] = {2, 2};
    union { qword q; } u;
    union { qword q; } v;
    CRef ref = func_00201360(2, aref, ak, &u, &v);
    ref.Decref();
    ref.InitTag(0x24);
    func_0019EAA0((char *)p + 0xF50, u.q, v.q);
    return ref;
}
