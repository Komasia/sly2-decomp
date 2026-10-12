typedef struct CRef { int m_tagk; int m_tag; } CRef;
typedef struct Q { char pad[0x10]; void *pv; } Q;
typedef struct P { char pad[0xC]; Q *pq; } P;
void func_0012A0B0(CRef *pref, int tagk);
void func_00127838(CRef *pref, void *pv);
void func_00129658(CRef *pref, CRef *prefSrc);
CRef *func_001291A8(CRef *pref, CRef *prefSrc);
void func_00129EC8(CRef *pref);
CRef *func_001266C8(CRef *ret, P *p)
{
    CRef ref;
    void *pv;
    ref.m_tagk = -1;
    pv = p->pq->pv;
    if (pv) {
        CRef tmp;
        func_00127838(&tmp, pv);
        func_00129658(&ref, &tmp);
        func_00129EC8(&tmp);
    } else {
        func_00129EC8(&ref);
        func_0012A0B0(&ref, 0x24);
    }
    func_001291A8(ret, &ref);
    func_00129EC8(&ref);
    return ret;
}
