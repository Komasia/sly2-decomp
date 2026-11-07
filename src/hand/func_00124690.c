typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
extern char D_003DD040[];
CRef *func_00124690(CRef *ret)
{
    CRef ref;
    ref.m_tagk = -1;
    SetBasic__4CRefP5BASIC(&ref, D_003DD040);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
