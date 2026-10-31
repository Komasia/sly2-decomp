/* func_001291E0: CRef constructor from a VECTOR: the value is copied into a reference-counted
 * slot from its splice slot heap (D_00452188), and the new reference holds it. */
#include "splice.h"
#include "slotheap.h"

typedef struct SLOTVECTOR {
    /* 0x00 */ qword qw;     /* the VECTOR */
    /* 0x10 */ int cref;
} SLOTVECTOR;

extern SLOTHEAP D_00452188;
void *func_0011CCC0(SLOTHEAP *pslotheap);   /* allocate a slot */

CRef *func_001291E0(CRef *pref, const qword *pqw)
{
    SLOTVECTOR *pslot;

    pref->m_tagk = TAGK_Vector;
    pslot = (SLOTVECTOR *)func_0011CCC0(&D_00452188);
    pslot->cref = 0;
    pref->m_tag.m_pv = pslot;
    pslot->cref++;
    *(qword *)pref->m_tag.m_pv = *pqw;
    return pref;
}
