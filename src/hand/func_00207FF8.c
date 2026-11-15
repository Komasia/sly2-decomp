/* func_00207FF8 (0x207FF8): sets the entries of the guard's kind array at +0xC10 (the loader's splice method). */
#include "h6_guard.h"
#define OFS_AKINDE 0xC10
void SetArrayKindes__FPvUi3OIDiT0(void *pguard, int grfEntries, int oid, int grf, KINDE *akinde);
void func_00207FF8(char *pguard, int grfEntries, int oid, int grf)
{
    SetArrayKindes__FPvUi3OIDiT0(pguard, grfEntries, oid, grf, (KINDE *)(pguard + OFS_AKINDE));
}
