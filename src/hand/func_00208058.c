/* func_00208058 (0x208058): sets the entries of the guard's kind array at +0xA70, resolved at once (the live splice method). */
#include "h6_guard.h"
#define OFS_AKINDE 0xA70
void func_00207F50(void *pguard, int grfEntries, int oid, int grf, KINDE *akinde);
void func_00208058(char *pguard, int grfEntries, int oid, int grf)
{
    func_00207F50(pguard, grfEntries, oid, grf, (KINDE *)(pguard + OFS_AKINDE));
}
