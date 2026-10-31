/* PwreGetWrCur (Sly 1 wr.c): the current warp entry; a caller about to change it marks the warp changed. */
#include "wr.h"

WRE *PwreGetWrCur(WR *pwr, ENSK ensk, WREK wrek)
{
    if (pwr->cwre == 0)
        return NULL;

    if (ensk == ENSK_Set)
        pwr->fValuesChanged = 1;

    return &pwr->awre[pwr->iwreCur];
}
