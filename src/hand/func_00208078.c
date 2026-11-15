/* func_00208078 (0x208078): sets the entries of the guard's kind array at +0x8D0 (the loader's splice method). */
#include "h6_guard.h"
#define OFS_AKINDE 0x8D0
void SetArrayKindes__FPvUi3OIDiT0(void *pguard, int grfEntries, int oid, int grf, KINDE *akinde);
void func_00208078(char *pguard, int grfEntries, int oid, int grf)
{
    SetArrayKindes__FPvUi3OIDiT0(pguard, grfEntries, oid, grf, (KINDE *)(pguard + OFS_AKINDE));
}
