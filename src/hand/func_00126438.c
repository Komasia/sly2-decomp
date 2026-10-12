typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
int func_00127D78(void *a, void *b, int c, CRef *d);
typedef struct BASIC { int pad[3]; void *p; } BASIC;
CRef *func_00126438(CRef *ret, BASIC *pbasic, void *aref)
{
    CRef ref;
    ref.m_tagk = -1;
    func_00127D78(aref, pbasic->p, 1, &ref);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
