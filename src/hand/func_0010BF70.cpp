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
CRef func_00201360(int c, void *aref, int *ak, void *an);
void *PloNearestPlayer(void *p, qword q) asm("PloNearestPlayer__FP6VECTORG9VU_VECTOR");
CRef func_0010BF70(void *p, int c, void *aref);
}
CRef func_0010BF70(void *p, int c, void *aref)
{
    union { qword q; } u;
    int k = 2;
    CRef ref = func_00201360(1, aref, &k, &u);
    ref = PloNearestPlayer(p, u.q);
    return ref;
}
