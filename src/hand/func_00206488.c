/* func_00206488 (0x206488): GUARD option setter (EOPID 254): the authored health from whole hits. */

#include "stepguard.h"
void func_00206488(struct GUARD *pguard, int cHits)
{
    pguard->nHealthMax = (cHits + 1) * 10;
}
