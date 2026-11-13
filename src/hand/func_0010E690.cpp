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
extern "C" { void func_001F8AD8(void *p, int a, int b, void *ps); CRef RefXfhMoveRot(void *p, int c, void *aref) asm("RefXfhMoveRot__FP5BASICiP4CRef"); }
struct BIG { qword aq[4]; };
// name: SafeHouse port (RefXfhMoveRot)
CRef RefXfhMoveRot(void *p, int c, void *aref)
{
    int ak[3] = {0x100D, 5, 4};
    BIG s;
    int a, b;
    CRef ref = RefSetArgsFromSplice(3, aref, ak, &a, &b, &s);
    ref.Decref();
    ref.InitTag(0x24);
    func_001F8AD8(p, a, b, &s);
    return ref;
}
