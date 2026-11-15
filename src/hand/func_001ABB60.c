/* func_001ABB60 (0x1ABB60): saves the game's slot to a card that may lack the save directory (the PMF D_002A6C90):
 * the card checked, the directory and its icon made (0x1AB7D0), the slot written (0x1AC420); an error puts the memory
 * card prompt in state 3. */
#include "h5_mc.h"
extern char g_cardprompt[] __asm__("D_002E6550");
void *func_001AC598(struct MC *pmc);
void *func_001AB7D0(struct MC *pmc);
void *func_001AC420(struct MC *pmc, void *pslot);
void func_001ACC38(void *pprompt, int state);
void *func_001ABB60(struct MC *pmc)
{
    void *nErr = func_001AC598(pmc); if (!nErr) nErr = func_001AB7D0(pmc); if (!nErr) nErr = func_001AC420(pmc, pmc->pslotGame); if (nErr) func_001ACC38(g_cardprompt, 3); return nErr;
}
