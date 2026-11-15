/* CRef::operator== (eqv?): same tag, then the payload by tag: scalars and objects by value / identity, matrices
 * bytewise, lm by 2 floats and vector / clq / smp by 3; other tags are equal by tag alone. */
#include "splice_tagk.h"
struct VECTOR { float x, y, z; };
struct VECTOR2 { float x, y; };
extern "C" int memcmp(const void *a, const void *b, int cb);
struct CRef {
    int m_tagk;
    union { int n; void *pv; VECTOR *pvec; VECTOR2 *pvec2; } u;
    bool operator==(const CRef &ref);
};
bool CRef::operator==(const CRef &ref)
{
    if (m_tagk != ref.m_tagk)
        return false;
    switch (m_tagk) {
    case TAGK_S32: case TAGK_F32: case TAGK_Bool: case TAGK_Symid: case TAGK_Bifk:
    case TAGK_Pair: case TAGK_Proc: case TAGK_Basic: case TAGK_Method: case TAGK_Err:
        return u.n == ref.u.n;
    case TAGK_Matrix:
        return memcmp(u.pv, ref.u.pv, 0x40) == 0;
    case TAGK_Lm:
        return u.pvec2->x == ref.u.pvec2->x && u.pvec2->y == ref.u.pvec2->y;
    case TAGK_Vector: case TAGK_Clq: case TAGK_Smp:
        return u.pvec->x == ref.u.pvec->x && u.pvec->y == ref.u.pvec->y && u.pvec->z == ref.u.pvec->z;
    }
    return true;
}
