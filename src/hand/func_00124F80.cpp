struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
extern "C" {
CRef func_001249A8(int k, void *a, void *b, void *c);
CRef func_00124F80(void *a, void *b, void *c);
}
CRef func_00124F80(void *a, void *b, void *c)
{
    CRef ref;
    ref = func_001249A8(0x7C, a, b, c);
    return ref;
}
