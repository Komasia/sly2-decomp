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
extern "C" CRef RefSetArgsFromSplice(int c, void *aref, int *ak, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void SetActorFollow__FP5ACTORiG9VU_VECTOR(void *p, int n, qword q); CRef func_0010A940(void *p, int c, void *aref); }
CRef func_0010A940(void *p, int c, void *aref)
{
    int ak[2] = {0x2002, 2};
    union { qword q; } u;
    int n;
    CRef ref = RefSetArgsFromSplice(2, aref, ak, &n, &u);
    ref.Decref();
    ref.InitTag(0x24);
    SetActorFollow__FP5ACTORiG9VU_VECTOR(p, n, u.q);
    return ref;
}
