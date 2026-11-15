/* func_001AC7A0 (0x1AC7A0): opens a file on the card (sceMcOpen); its descriptor is returned through pfd.
 * Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* waits for the sceMc call (0x1AB098) */
int sceMcOpen(int port, int slot, const char *szFile, int mode);

int func_001AC7A0(MC *pmc, const char *szFile, int mode, int *pfd)
{
    return FUN_0018bc90(pmc->memcard, sceMcOpen(pmc->port, pmc->slot, szFile, mode), 2, pfd);
}
