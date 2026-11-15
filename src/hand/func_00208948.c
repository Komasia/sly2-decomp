/* func_00208948 (0x208948): removes a class from the guard's excluded classes (moving on after each removal, as the game does). */
#include "stepguard.h"
void *s1_memmove(void *pvDst, void *pvSrc, int cb) asm("memmove");
void func_00208948(struct GUARD *pguard, int cid)
{
    int icid;
    for (icid = 0; icid < pguard->ccidExcluded; icid++) {
        if (pguard->acidExcluded[icid] == cid) {
            s1_memmove(pguard->acidExcluded + icid, pguard->acidExcluded + icid + 1, (pguard->ccidExcluded - icid) * 4 - 4);
            pguard->ccidExcluded--;
        }
    }
}
