#include "splice.h"
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void func_001294C0(CRef *pref, void *p);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 129: PsndNewPlain + SetSource)
CRef *RefOpStartSound__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int n = aref[1].m_tag.m_n;
    void *p = PsndNewPlain__Fi(aref[0].m_tag.m_n);
    SetSource__4CSndPv(p, n);
    func_001294C0(ret, p);
    return ret;
}
