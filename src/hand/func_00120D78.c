/* BIF nth: the n-th element of a list. */
#include "splice.h"
typedef struct PAIR { int a; int b; CRef ref; struct PAIR *pnext; } PAIR;
void InitTag(CRef *pref, int tagk) asm("InitTag__4CRef");
void __as__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void Decref(CRef *pref) asm("Decref__4CRef");
CRef *RefOpNth__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    InitTag(&ref, TAGK_None);
    if (aref[0].m_tagk == TAGK_Pair) {
        PAIR *p = (PAIR *)aref[0].m_tag.m_pv;
        CRef *pn = &aref[1];
        int i;
        for (i = 0; p; p = p->pnext, i++) {
            if (i == pn->m_tag.m_n) {
                __as__4CRefRC4CRef(&ref, &p->ref);
                break;
            }
        }
    }
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
