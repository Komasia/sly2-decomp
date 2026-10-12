typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
void Decref__4CRef(CRef *pref);
void func_00129DA8(CRef *pref, CRef *prefSrc);
float func_0011D948(int n, float g);
CRef *func_001235A8(CRef *ret, void *pbasic, CRef *aref)
{
    int n = aref[0].u.n;
    CRef ref;
    float g;
    func_00129DA8(&ref, &aref[1]);
    g = func_0011D948(n, ref.u.g);
    ret->u.g = g;
    ret->m_tagk = 0x16;
    Decref__4CRef(&ref);
    return ret;
}
