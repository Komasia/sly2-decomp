/* func_00206458 (0x206458): GUARD option getter (EOPID 254): the authored health in whole hits. */

#include "stepguard.h"
int func_00206458(struct GUARD *pguard)
{
    int nTenths = pguard->nHealthMax - 1;
    return (nTenths <= -1 ? 0 : nTenths) / 10;
}
