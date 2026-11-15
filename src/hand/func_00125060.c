/* BIF 126 convert-object-vector: the direction aref[2] taken from object aref[0]'s space to aref[1]'s. */
#include "splice.h"
typedef int TI __attribute__((mode(TI)));
TI ConvertVec__FP2LOT0G9VU_VECTOR(void *a, void *b, TI v);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 126: ConvertVec)
CRef *RefOpConvertObjectVector__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    TI *pv;
    InitTag__4CRef(&ref, TAGK_Vector);
    pv = ref.m_tag.m_pv;
    *pv = ConvertVec__FP2LOT0G9VU_VECTOR(aref[0].m_tag.m_pv, aref[1].m_tag.m_pv, *(TI *)aref[2].m_tag.m_pv);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
