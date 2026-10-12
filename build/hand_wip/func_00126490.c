/* 2 diff: sw -1 to ref scheduled after "daddu a0,s0" (target: before). C++ form gives same. */
typedef struct CRef { int m_tagk; union { int n; float g; void *pv; } u; } CRef;
typedef struct Q { char pad[0xC]; void *pv0C; void *pv10; } Q;
typedef struct R { char pad[0x10]; Q *pq; } R;
typedef struct P { char pad[0xC]; R *pr; } P;
void Decref__4CRef(CRef *pref);
CRef *func_001291A8(CRef *pref, CRef *prefSrc);
CRef *func_00129658(CRef *pref, CRef *prefSrc);
CRef *func_00127838(CRef *ret, void *pv);
CRef *func_00127CF0(CRef *ret, CRef *aref, void *pv, CRef *pref);
CRef *func_00126490(CRef *ret, P *p, CRef *aref)
{
    CRef ref;
    CRef tmp;
    Q *pq;
    ref.m_tagk = -1;
    pq = p->pr->pq;
    func_00127838(&tmp, pq->pv10);
    func_00129658(&ref, &tmp);
    Decref__4CRef(&tmp);
    func_00127CF0(&tmp, aref, pq->pv0C, &ref);
    func_00129658(&ref, &tmp);
    Decref__4CRef(&tmp);
    func_001291A8(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
