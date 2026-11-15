/* BIF 125 convert-object-position: the point aref[2] taken from object aref[0]'s space to aref[1]'s (nil: the
 * world). */
#include "splice.h"
typedef int TI __attribute__((mode(TI)));
void func_00129248(CRef *pref, TI vec);
TI ConvertPos__FP2LOT0G9VU_VECTOR(int a, int b, TI v);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 125: ConvertPos)
CRef *RefOpConvertObjectPosition__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    func_00129248(&ref, ConvertPos__FP2LOT0G9VU_VECTOR(aref[0].m_tag.m_n, aref[1].m_tag.m_n, *(TI *)aref[2].m_tag.m_pv));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
