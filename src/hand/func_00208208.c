/* func_00208208 (0x208208): each of 26 kind entries cleared (0x209590). */
#include "h6_guard.h"
void func_00209590(KINDE *pkinde);
void func_00208208(void *pguard, KINDE *pkinde) { int i; for (i = 25; i >= 0; i--) { func_00209590(pkinde); pkinde++; } }
