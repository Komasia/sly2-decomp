/* class: a splice built-in (BIF 99: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 99 the current episode, 0x210AE0) - the result is an int CRef (tag 0x15). */
#include "splice.h"

int func_00210AE0(void);

CRef *func_00123A98(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    pref->m_tag.m_n = func_00210AE0();
    pref->m_tagk = TAGK_S32;
    return pref;
}
