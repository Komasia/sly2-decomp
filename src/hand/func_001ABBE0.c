/* func_001ABBE0 (0x1ABBE0): saves the game's slot (run on the card thread by the PMF D_002A6C88): the card checked
 * (0x1AC598), then the slot written (0x1AC420); on an error the memory card prompt D_002E6550 shows message 0x23 in
 * state 3 and the save icon D_002E65A0 is hidden (0x1ADE70). Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
int func_001AC598(MC *pmc);
int FUN_0018d2e8(MC *pmc, MCSLOT *pslot);
void func_001ACC38(void *pprompt, int state);
void func_001ACB58(void *pprompt, int msg);
void func_001ADE70(void *pwidget);
extern char g_cardprompt[] __asm__("D_002E6550");   /* the memory card prompt */
extern char g_saveicon[] __asm__("D_002E65A0");

int func_001ABBE0(MC *pmc)
{
    int nErr = func_001AC598(pmc);

    if (nErr != 0 || (nErr = FUN_0018d2e8(pmc, pmc->pslotGame)) != 0) {
        func_001ACC38(g_cardprompt, 3);
        func_001ACB58(g_cardprompt, 0x23);
        func_001ADE70(g_saveicon);
    }
    return nErr;
}
