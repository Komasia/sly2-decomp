/* CRef::SetTag (Sly 1 ref.h; SafeHouse ref.h "InitTag 0x12A0B0"): gives the reference a tag. The kinds with a
 * pooled payload (vector, matrix, clq, lm, smp) get a fresh node holding one reference; every other kind starts
 * with a null payload. */
#include "splice_ref.h"
void InitTag__4CRef(CRef *pref, int tagk)
{
    pref->m_tagk = tagk;
    switch (tagk) {
    case TAGK_Vector: {
        REFVECTOR *p = (REFVECTOR *)func_0011CCC0(&D_00452188);
        p->cref = 0;
        pref->m_tag.m_pv = p;
        p->cref++;
        break;
    }
    case TAGK_Matrix: {
        REFMATRIX *p = (REFMATRIX *)func_0011CCC0(&D_004521A0);
        p->cref = 0;
        pref->m_tag.m_pv = p;
        p->cref++;
        break;
    }
    case TAGK_Clq: {
        REFCLQ *p = (REFCLQ *)func_0011CCC0(&D_004521B8);
        p->cref = 0;
        pref->m_tag.m_pv = p;
        p->cref++;
        break;
    }
    case TAGK_Lm: {
        REFLM *p = (REFLM *)func_0011CCC0(&D_004521D0);
        p->cref = 0;
        pref->m_tag.m_pv = p;
        p->cref++;
        break;
    }
    case TAGK_Smp: {
        REFSMP *p = (REFSMP *)func_0011CCC0(&D_004521E8);
        p->cref = 0;
        pref->m_tag.m_pv = p;
        p->cref++;
        break;
    }
    case TAGK_Pair:
    case TAGK_Proc:
    case TAGK_Basic:
    case TAGK_Method:
    case 0x23:      /* TAGK_Err in SafeHouse (unconfirmed) */
    default:
        pref->m_tag.m_pv = 0;
        break;
    }
}
