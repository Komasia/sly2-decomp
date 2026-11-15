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
CRef RefPairFromAplo__FiPP2LO(int c, void **ap);
CRef RefOpFindClassObjects(void *pbasic, CRef *aref) asm("RefOpFindClassObjects__FiP4CRefP6CFrame");
}
// name: Sly 1 bif.cpp RefOpFindClassObjects (BIF 120: CFindObjectsByClass; Sly 1 order FindCameraObject, FindClassObjects, FindObjectsInBoundingBox; was RefOpFindObjects, which is BIF 113 0x1241E8)
CRef RefOpFindClassObjects(void *pbasic, CRef *aref)
{
    CRef ref;
    void *ap[0x180];
    int b = aref[1].u.n;
    int c = CFindObjectsByClass(g_sw, b ? 0x401 : 0x405, aref[0].u.pv, b, 0x180, ap);
    ref = RefPairFromAplo__FiPP2LO(c, ap);
    return ref;
}
