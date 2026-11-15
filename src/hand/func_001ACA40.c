/* func_001ACA40 (0x1ACA40): deletes a file from the card (sceMcDelete); "no such file" (result 0xE) is not an
 * error. Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* waits for the sceMc call (0x1AB098) */
int sceMcDelete(int port, int slot, const char *szFile);

int func_001ACA40(MC *pmc, const char *szFile)
{
    int nErr = FUN_0018bc90(pmc->memcard, sceMcDelete(pmc->port, pmc->slot, szFile), 0xF, 0);

    return (nErr == 0xE) ? 0 : nErr;
}
