/* func_001AC6A0 (0x1AC6A0): the card's free space in bytes (sceMcGetInfo's 1 KB clusters << 10) through pcbFree, 0
 * on an error (a new card is not one; unformatted gives 12). Layout: include/h5_mc.h. */
#include "h5_mc.h"
int sceMcGetInfo(int port, int slot, int *ptype, int *pcfree, int *pfFormatted);
int func_001AB098(void *pmemcard, int nResult, int kind, int pn);
int func_001AC6A0(struct MC *pmc, int *pcbFree)
{
    void *pmemcard = pmc->memcard;
    int nResult;
    int nErr;
    nResult = sceMcGetInfo(pmc->port, pmc->slot, &pmc->typeCard, &pmc->cclusterFree, &pmc->fFormatted);
    nErr = func_001AB098(pmemcard, nResult, 1, 0);
    switch (nErr) {
    case 9:
        nErr = 0;
        break;
    case 10:
        nErr = 12;
        break;
    }
    if (nErr == 0)
        *pcbFree = pmc->cclusterFree << 10;
    else
        *pcbFree = 0;
    return nErr;
}
