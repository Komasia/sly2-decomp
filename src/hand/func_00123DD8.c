/* class: a splice built-in (BIF 106: its pointer in the BIF table g_mpbifkbif 0x2BBB90; SafeHouse gamebif.cpp:
 * 106 the cancel of a scheduled callback, 0x133130): cancels the callback of id aref[0]; the result is void. */
#include "splice.h"

void func_00133130(void *psw, int id);   /* cancel the scheduled callback id */
extern char g_sw[];

CRef *func_00123DD8(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    func_00133130(g_sw, aref[0].m_tag.m_n);
    InitTag__4CRef(pref, TAGK_Void);
    return pref;
}
