/* func_002064A0 (0x2064A0): GUARD option getter (EOPID 255): the hit points left. */

#include "stepguard.h"
int func_002064A0(struct GUARD *pguard)
{
    int nHealthLess1 = pguard->nHealth - 1;
    return (nHealthLess1 <= -1 ? 0 : nHealthLess1) + 1;
}
