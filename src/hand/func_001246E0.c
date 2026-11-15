#include "splice.h"
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
extern char g_cm[];
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 119: the camera g_cm, as Sly 1)
CRef *RefOpFindCameraObject__FiP4CRefP6CFrame(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    SetBasic__4CRefP5BASIC(&ref, g_cm);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
