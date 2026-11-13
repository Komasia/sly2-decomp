typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(qword q);
};
extern "C" {
CRef RefSetArgsFromSplice(int c, void *aref, int *ak, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
qword func_001E77B0(void *p, qword q);
CRef func_0010E550(void *p, int c, void *aref);
}
CRef func_0010E550(void *p, int c, void *aref)
{
    union { qword q; } u;
    int k = 2;
    CRef ref = RefSetArgsFromSplice(1, aref, &k, &u);
    ref = func_001E77B0(p, u.q);
    return ref;
}
