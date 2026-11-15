/* func_001AB6C0 (0x1AB6C0): formats the card (sceMcFormat; run on the card thread by the PMF D_002A6E88); on an error
 * the card is MCS_UNFORMATTED and the memory card prompt D_002E6550 goes to state 3, else MCS_READY.
 * Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* waits for the sceMc call (0x1AB098) */
int sceMcFormat(int port, int slot);
void func_001ACC38(void *pprompt, int state);
extern char g_cardprompt[] __asm__("D_002E6550");   /* the memory card prompt */

int func_001AB6C0(MC *pmc)
{
    int nErr = FUN_0018bc90(pmc->memcard, sceMcFormat(pmc->port, pmc->slot), 0x10, 0);

    if (nErr != 0) {
        pmc->stateWanted = MCS_UNFORMATTED;
        func_001ACC38(g_cardprompt, 3);
    } else {
        pmc->stateWanted = MCS_READY;
    }
    return nErr;
}
