typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void func_00129598(CRef *pref, int f);
int func_001DAEA8(int n);
CRef *func_001256E0(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    ref.m_tagk = -1;
    func_00129598(&ref, func_001DAEA8(aref->m_tag) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
