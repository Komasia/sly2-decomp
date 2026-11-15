/* func_002064C0 (0x2064C0): GUARD option setter (EOPID 255): the hit points left from whole hits. */

#include "stepguard.h"
void func_002064C0(struct GUARD *pguard, int cHits)
{
    pguard->nHealth = (cHits + 1) * 10;
}
