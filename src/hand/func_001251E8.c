typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void func_001294C0(CRef *pref, void *p);
CRef *func_001251E8(CRef *ret, void *pbasic, CRef *aref)
{
    int n = aref[1].m_tag;
    void *p = PsndNewPlain__Fi(aref[0].m_tag);
    SetSource__4CSndPv(p, n);
    func_001294C0(ret, p);
    return ret;
}
