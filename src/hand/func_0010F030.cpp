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
extern "C" { void func_00163838(void *p, int, void *, int, int); CRef func_0010F030(void *p, int c, void *aref); }
CRef func_0010F030(void *p, int c, void *aref)
{
    int ak[4] = {0x6, 0x9050, 0x6, 0xf};
    CRef v1;
    int v0;
    int v2;
    int v3;
    CRef ref = RefSetArgsFromSplice(4, aref, ak, &v0, &v1, &v2, &v3);
    ref.Decref();
    ref.InitTag(0x24);
    func_00163838(p, v0, &v1, v2, v3);
    return ref;
}
