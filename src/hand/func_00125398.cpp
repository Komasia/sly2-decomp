struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct OBJ { int a[4]; OBJ(); ~OBJ(); };
struct X { int a[4]; };
extern char D_003E0EA8[];
extern char D_003D4A60[];
extern "C" {
void AkeyFromList(void *pv, X *px) asm("AkeyFromList__FP4CRefP3ARR");
CRef RefGetProgress(void *a, X *px, void *b) asm("RefGetProgress__FP4TRIEP3KEYPc");
CRef func_00125398(void *pbasic, CRef *aref);
}
CRef func_00125398(void *pbasic, CRef *aref)
{
    CRef ref;
    OBJ obj;
    X x;
    AkeyFromList(aref[0].u.pv, &x);
    ref = RefGetProgress(D_003E0EA8, &x, D_003D4A60);
    return ref;
}
