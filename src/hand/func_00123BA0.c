/* class: a splice built-in (BIF 104: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 104 0, 0x210B68) - the result is an int CRef (tag 0x15). */
#include "splice.h"

int func_00210B68(void);

CRef *func_00123BA0(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    pref->m_tag.m_n = func_00210B68();
    pref->m_tagk = TAGK_S32;
    return pref;
}
