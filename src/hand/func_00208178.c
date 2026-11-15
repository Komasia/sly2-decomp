/* func_00208178 (0x208178): each entry of one of the guard's 26-entry kind arrays cleared (0x2090D0). */
#include "h6_guard.h"
typedef struct GUARD GUARD;

void func_002090D0(KINDE *pkinde, GUARD *pguard);   /* clears the entry (frees its KIND2 / KIND3) */

void func_00208178(GUARD *pguard, KINDE *akinde)
{
    int i;

    for (i = 0; i < 26; i++) {
        func_002090D0(&akinde[i], pguard);
    }
}
