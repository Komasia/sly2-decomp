typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
};
extern "C" {
CRef func_00201360(int c, void *aref, int *ak, void *a0, void *a1);
void *func_001F8510(void *p, int a, int b);
CRef func_001014E8(void *p, int c, void *aref);
}
CRef func_001014E8(void *p, int c, void *aref)
{
    int ak[2] = {2, 2};
    int a, b;
    CRef ref = func_00201360(2, aref, ak, &a, &b);
    ref = func_001F8510(p, a, b);
    return ref;
}
