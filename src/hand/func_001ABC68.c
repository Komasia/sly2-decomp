/* func_001ABC68 (0x1ABC68): starts a new save on the card (the PMF D_002A6E90): the card checked, the directory and
 * its icon made (0x1AB7D0), the chosen slot written fresh (0x1AC468); an error puts the memory card prompt in
 * state 3. */
#include "h5_mc.h"
extern char g_cardprompt[] __asm__("D_002E6550");
void *func_001AC598(struct MC *pmc);
void *func_001AB7D0(struct MC *pmc);
void *func_001AC468(struct MC *pmc, void *pslot);
void func_001ACC38(void *pprompt, int state);
void *func_001ABC68(struct MC *pmc)
{
    void *nErr = func_001AC598(pmc); if (!nErr) nErr = func_001AB7D0(pmc); if (!nErr) nErr = func_001AC468(pmc, pmc->pslotChosen); if (nErr) func_001ACC38(g_cardprompt, 3); return nErr;
}
