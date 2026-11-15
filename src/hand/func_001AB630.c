/* func_001AB630 (0x1AB630): in MCS_SAVES with a read slot (D_003E0EA8), the card's three slots are validated
 * (0x1AC570; SafeHouse frontend.cpp: "the card's slots read at the world's start") and the card moves to
 * MCS_SLOTS (0x1AB418: the newest slot chosen). Layout: include/h5_mc.h. */
#include "h5_mc.h"
typedef struct MC MC;
typedef struct MCSLOT MCSLOT;
extern int g_pslotRead __asm__("D_003E0EA8");
void SetMemcardThreadHighPrio__FP7MEMCARD(void *pmemcard);
int func_001AC570(MC *pmc, MCSLOT *pslot);
void func_001AB418(MC *pmc, int state);

void func_001AB630(MC *pmc)
{
    if (pmc->state == MCS_SAVES && g_pslotRead != 0) {
        MCSLOT *pslot = pmc->aslot;
        int i;

        SetMemcardThreadHighPrio__FP7MEMCARD(pmc->memcard);
        for (i = 2; i >= 0; i--) {
            func_001AC570(pmc, pslot);
            pslot++;
        }
        pmc->stateWanted = MCS_SLOTS;
        func_001AB418(pmc, MCS_SLOTS);
    }
}
