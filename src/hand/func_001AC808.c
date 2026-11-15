/* func_001AC808 (0x1AC808): closes a card file (sceMcClose). Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* waits for the sceMc call (0x1AB098) */
int sceMcClose(int fd);

int func_001AC808(MC *pmc, int fd)
{
    return FUN_0018bc90(pmc->memcard, sceMcClose(fd), 3, 0);
}
