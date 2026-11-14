/* class: a splice built-in (BIF 98: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 98 the current world record's kind, 0x210A98) - the result is an int CRef (tag 0x15). */
#include "splice.h"

int func_00210A98(void);

CRef *func_00123A60(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    pref->m_tag.m_n = func_00210A98();
    pref->m_tagk = TAGK_S32;
    return pref;
}
