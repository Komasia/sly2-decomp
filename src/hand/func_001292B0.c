/* func_001292B0: CRef constructor from a MATRIX4: the matrix is copied into a
 * reference-counted slot from the splice matrix slot heap (D_004521A0), and the new reference holds it. */
#include "splice.h"
#include "slotheap.h"

typedef struct SLOTMATRIX {
    /* 0x00 */ qword aqw[4];   /* the MATRIX4 */
    /* 0x40 */ int cref;
} SLOTMATRIX;

extern SLOTHEAP D_004521A0;
void *func_0011CCC0(SLOTHEAP *pslotheap);   /* allocate a slot */

CRef *func_001292B0(CRef *pref, const qword *paqw)
{
    SLOTMATRIX *pslot;
    SLOTMATRIX *pslotNew;

    pref->m_tagk = TAGK_Matrix;
    pslot = (SLOTMATRIX *)func_0011CCC0(&D_004521A0);
    pslot->cref = 0;
    pref->m_tag.m_pv = pslot;
    pslot->cref++;
    pslotNew = (SLOTMATRIX *)pref->m_tag.m_pv;
    pslotNew->aqw[0] = paqw[0];
    pslotNew->aqw[1] = paqw[1];
    pslotNew->aqw[2] = paqw[2];
    pslotNew->aqw[3] = paqw[3];
    return pref;
}
