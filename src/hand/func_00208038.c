/* func_00208038 (0x208038): sets the entries of the guard's kind array at +0xA70 (the loader's splice method). */
#include "h6_guard.h"
#define OFS_AKINDE 0xA70
void SetArrayKindes__FPvUi3OIDiT0(void *pguard, int grfEntries, int oid, int grf, KINDE *akinde);
void func_00208038(char *pguard, int grfEntries, int oid, int grf)
{
    SetArrayKindes__FPvUi3OIDiT0(pguard, grfEntries, oid, grf, (KINDE *)(pguard + OFS_AKINDE));
}
