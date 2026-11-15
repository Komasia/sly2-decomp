/* func_002080A0 (0x2080A0): each entry of one of the guard's 26-entry kind arrays resolved (ResolveKinde). */
#include "h6_guard.h"
typedef struct GUARD GUARD;

void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, GUARD *pguard);

void func_002080A0(GUARD *pguard, KINDE *akinde)
{
    int i;

    for (i = 0; i < 26; i++) {
        ResolveKinde__FP5KINDEP5GUARD(&akinde[i], pguard);
    }
}
