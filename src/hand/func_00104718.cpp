typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(bool f);
};
extern "C" {
CRef func_00201360(int c, void *aref, int *ak, void *a0);
int FPointInShape(void *p, qword q) asm("FPointInShape__FP2LOG9VU_VECTOR");
CRef func_00104718(void *p, int c, void *aref);
}
CRef func_00104718(void *p, int c, void *aref)
{
    int ak[1] = {2};
    union { qword q; } u;
    CRef ref = func_00201360(1, aref, ak, &u);
    ref = FPointInShape(p, u.q) != 0;
    return ref;
}
