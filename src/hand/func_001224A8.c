/* A unary float operation (sqrt, sin, cos, ... by UFOK, the function table at 0x2BBB70) on a number. */
#include "splice.h"
typedef float (*PFNG)(float);
extern PFNG D_002BBB70[];
void SetF32__4CReff(CRef *pref, float g);
void Decref(CRef *pref) asm("Decref__4CRef");
CRef *RefUfo__FP4CRef4UFOK(CRef *ret, CRef *parg, int i)
{
    CRef ref;
    float g;
    ref.m_tagk = TAGK_Nil;
    if (parg->m_tagk == TAGK_F32) {
        g = parg->m_tag.m_g;
    } else {
        g = (float)parg->m_tag.m_n;
    }
    SetF32__4CReff(&ref, D_002BBB70[i](g));
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
