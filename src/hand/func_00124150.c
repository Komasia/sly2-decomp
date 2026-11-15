#include "splice.h"
typedef struct LO { char pad[0xC]; struct LO *pc; char pad2[0x2C]; void *pv; } LO;
typedef struct G { char pad[0x3F0C]; void *pv; } G;
extern G g_sw;
void *PloFindSwObject__FP2SWi3OIDP2LOPv(G *pg, int k, int a, LO *b, void *c);
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 112: PloFindSwObject, relative 1 / global 5)
CRef *RefOpFindObject__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    LO *b;
    LO *plo;
    void *pv;
    ref.m_tagk = TAGK_Nil;
    b = (LO *)aref[1].m_tag.m_pv;
    if (aref[2].m_tagk) {
        plo = ((LO *)aref[2].m_tag.m_pv)->pc;
    } else {
        plo = b;
    }
    {
        G *pg = &g_sw;
        int k = b ? 1 : 5;
        int a = aref[0].m_tag.m_n;
        SetBasic__4CRefP5BASIC(&ref, PloFindSwObject__FP2SWi3OIDP2LOPv(pg, k, a, b, plo ? plo->pv : pg->pv));
    }
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
