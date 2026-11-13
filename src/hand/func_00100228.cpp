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
CRef RefSetArgsFromSplice(int c, void *aref, int *ak, int *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
int FIsBasicDerivedFrom(void *p, int n) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
CRef func_00100228(void *p, int c, void *aref);
}
CRef func_00100228(void *p, int c, void *aref)
{
    int k = 7;
    int n;
    CRef ref = RefSetArgsFromSplice(1, aref, &k, &n);
    ref = FIsBasicDerivedFrom(p, n) != 0;
    return ref;
}
