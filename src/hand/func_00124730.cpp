struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
extern char g_sw[];
extern "C" {
int CFindObjectsByClass(void *pg, int k, void *a, int b, int c, void **ap) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
CRef func_00124078(int c, void **ap);
CRef func_00124730(void *pbasic, CRef *aref);
}
CRef func_00124730(void *pbasic, CRef *aref)
{
    CRef ref;
    void *ap[0x180];
    int b = aref[1].u.n;
    int c = CFindObjectsByClass(g_sw, b ? 0x401 : 0x405, aref[0].u.pv, b, 0x180, ap);
    ref = func_00124078(c, ap);
    return ref;
}
