/* class: a splice built-in (BIF 103: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 103 a float of 0x2DE578, 0x154C90 GSuck) - the result is a float CRef (tag 0x16). */
#include "splice.h"

float GSuck__FPv(void *psuck);
extern char D_002DE578[];   /* the suck meter */

CRef *func_00123B60(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    pref->m_tag.m_g = GSuck__FPv(D_002DE578);
    pref->m_tagk = TAGK_F32;
    return pref;
}
