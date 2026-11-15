#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *p, int n, float g);
extern char g_joy[];
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 130: TriggerJoyRumbleRumk on the pad)
CRef *RefOpStartRumble__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    void *p = g_joy;
    int n = aref[0].m_tag.m_n;
    CRef ref;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    TriggerJoyRumbleRumk__FP3JOY4RUMKf(p, n, ref.m_tag.m_g);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, TAGK_Void);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
