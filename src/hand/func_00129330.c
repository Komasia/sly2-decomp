/* func_00129330: CRef constructor from a CLQ: the value is copied into a reference-counted
 * slot from its splice slot heap (D_004521B8), and the new reference holds it. */
#include "splice.h"
#include "slotheap.h"

typedef struct SLOTCLQ {
    /* 0x00 */ qword qw;     /* the CLQ */
    /* 0x10 */ int cref;
} SLOTCLQ;

extern SLOTHEAP D_004521B8;
void *func_0011CCC0(SLOTHEAP *pslotheap);   /* allocate a slot */

CRef *func_00129330(CRef *pref, const qword *pqw)
{
    SLOTCLQ *pslot;

    pref->m_tagk = TAGK_Clq;
    pslot = (SLOTCLQ *)func_0011CCC0(&D_004521B8);
    pslot->cref = 0;
    pref->m_tag.m_pv = pslot;
    pslot->cref++;
    *(qword *)pref->m_tag.m_pv = *pqw;
    return pref;
}
