/* func_00208018 (0x208018): sets the entries of the guard's kind array at +0xC10, resolved at once (the live splice method). */
#include "h6_guard.h"
#define OFS_AKINDE 0xC10
void func_00207F50(void *pguard, int grfEntries, int oid, int grf, KINDE *akinde);
void func_00208018(char *pguard, int grfEntries, int oid, int grf)
{
    func_00207F50(pguard, grfEntries, oid, grf, (KINDE *)(pguard + OFS_AKINDE));
}
