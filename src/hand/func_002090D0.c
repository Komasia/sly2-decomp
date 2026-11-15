/* func_002090D0 (0x2090D0): clears a guard kind entry: a KIND2 / KIND3 payload goes back to its slot heap
 * (0x20C030 / 0x20CA20), then no kind and no oid (SafeHouse guardstart.cpp: "resets the entry's kind payload"). */
#include "h6_guard.h"
typedef struct GUARD GUARD;

void func_0020C030(KIND2 *pk2);   /* frees a KIND2 */
void func_0020CA20(KIND3 *pk3);   /* frees a KIND3 */

void func_002090D0(KINDE *pkinde, GUARD *pguard)
{
    if (pkinde->k != KINDK_Kind2) {
        if (pkinde->k == KINDK_Kind3) {
            func_0020CA20(pkinde->u.pk3);
            pkinde->u.pk3 = 0;
        }
    } else {
        func_0020C030(pkinde->u.pk2);
        pkinde->u.pk2 = 0;
    }
    pkinde->u.oid = -1;
    pkinde->k = KINDK_None;
}
