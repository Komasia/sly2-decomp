/* class: a splice built-in (BIF 97: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 97 the world's index, 0x210A88) - the result is an int CRef (tag 0x15). */
#include "splice.h"

int func_00210A88(void);

CRef *func_00123A28(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    pref->m_tag.m_n = func_00210A88();
    pref->m_tagk = TAGK_S32;
    return pref;
}
