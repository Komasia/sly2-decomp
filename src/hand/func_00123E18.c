/* BIF 107 defer-object-update (object dt): the object's next update waits until t + dt (LO +0x30); void. */
#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
extern float g_clock;
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 107: sets the object's next update time +0x30 to now + dt; SafeHouse 107 defer-object-update)
CRef *RefOpDeferObjectUpdate__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    CRef refT;
    char *p;
    float g;
    InitTag__4CRef(&ref, TAGK_Void);
    p = (char *)aref[0].m_tag.m_pv;
    RefCoerceF32__4CRef(&refT, &aref[1]);
    g = refT.m_tag.m_g;
    Decref__4CRef(&refT);
    *(float *)(p + 0x30) = g_clock + g;
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
