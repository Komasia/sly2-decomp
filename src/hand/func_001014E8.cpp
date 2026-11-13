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
CRef RefSetArgsFromSplice(int c, void *aref, int *ak, void *a0, void *a1) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
void *func_001F8510(void *p, int a, int b);
CRef RefXfHandle(void *p, int c, void *aref) asm("RefXfHandle__FP2LOiPv");
}
// name: SafeHouse port (RefXfHandle)
CRef RefXfHandle(void *p, int c, void *aref)
{
    int ak[2] = {6, 0x104c};
    int a, b;
    CRef ref = RefSetArgsFromSplice(2, aref, ak, &a, &b);
    ref = func_001F8510(p, a, b);
    return ref;
}
