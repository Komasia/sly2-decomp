/* func_001AC598 (0x1AC598): checks the card (sceMcGetInfo: its type, free space and format) and sets the wanted
 * state from the result: no card / not a PS2 card -> MCS_NO_CARD, unformatted -> MCS_UNFORMATTED, a new card ->
 * at least MCS_READY; the next check in 0.3 s (g_clock.tReal). Layout: include/h5_mc.h. */
#include "h5_mc.h"
#define MCTYPE_PS2 2
extern float g_tReal __asm__("D_002DDF0C");  /* g_clock.tReal */
int sceMcGetInfo(int port, int slot, int *ptype, int *pcfree, int *pfFormatted);
int func_001AB098(void *pmemcard, int nResult, int kind, int pn);
int func_001AC598(struct MC *pmc)
{
    void *pmemcard = pmc->memcard;
    int nResult;
    int nErr;
    nResult = sceMcGetInfo(pmc->port, pmc->slot, &pmc->typeCard, &pmc->cclusterFree, &pmc->fFormatted);
    nErr = func_001AB098(pmemcard, nResult, 1, 0);
    switch (nErr) {
    case 11:
        pmc->stateWanted = MCS_NO_CARD;
        break;
    case 9:
        pmc->stateWanted = MCS_READY;
        break;
    case 10:
    case 12:
        nErr = 12;
        pmc->stateWanted = MCS_UNFORMATTED;
        break;
    case 0:
        if (pmc->fFormatted) { if (pmc->stateWanted < MCS_READY) pmc->stateWanted = MCS_READY; } else pmc->stateWanted = MCS_UNFORMATTED;
        break;
    }
    if (nErr == 0 || nErr == 12) {
        if (pmc->typeCard != MCTYPE_PS2) {
            nErr = 11;
            pmc->stateWanted = MCS_NO_CARD;
        }
    }
    pmc->tPoll = g_tReal + 0.3f;
    return nErr;
}
