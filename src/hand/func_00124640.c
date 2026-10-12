typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void func_00129A10(CRef *pref, void *p);
extern char D_003DD490[];
CRef *func_00124640(CRef *ret)
{
    CRef ref;
    ref.m_tagk = -1;
    func_00129A10(&ref, D_003DD490);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
