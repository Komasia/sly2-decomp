/* BIF hit-test-objects-first (BIFK 0x7C): RefOpHitTestObjectsImpl with that kind (the first hit). */
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
extern "C" {
CRef RefOpHitTestObjectsImpl__F4BIFKiP4CRefP6CFrame(int k, void *a, void *b, void *c);
CRef RefOpHitTestObjectsFirst__FiP4CRefP6CFrame(void *a, void *b, void *c);
}
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 124: RefOpHitTestObjectsImpl with its own BIFK 0x7C)
CRef RefOpHitTestObjectsFirst__FiP4CRefP6CFrame(void *a, void *b, void *c)
{
    CRef ref;
    ref = RefOpHitTestObjectsImpl__F4BIFKiP4CRefP6CFrame(0x7C, a, b, c);
    return ref;
}
