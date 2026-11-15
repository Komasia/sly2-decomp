/* func_001AC748 (0x1AC748): makes a directory on the card (sceMcMkdir); "already exists" (result 0x18) is not an
 * error. Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* waits for the sceMc call (0x1AB098) */
int sceMcMkdir(int port, int slot, const char *szDir);

int func_001AC748(MC *pmc, const char *szDir)
{
    int nErr = FUN_0018bc90(pmc->memcard, sceMcMkdir(pmc->port, pmc->slot, szDir), 0xB, 0);

    return (nErr == 0x18) ? 0 : nErr;
}
