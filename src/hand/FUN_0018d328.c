/* FUN_0018d328 (0x1AC468): writes a fresh save slot to the card: the slot reset (keeping the settings), then its data
 * (0x5408 bytes) written to its file. */
#include "h5_mc.h"
#define CB_SAVE 0x5408
void ResetSlotKeepSettings__FPci(struct MCSLOT *pslot, int f);
void func_001ABB10(void *pmc, void *pslot, char *szName);
int func_001AC900(void *pmc, char *szName, void *pv, int cb);
int FUN_0018d328(void *pmc, struct MCSLOT *pslot)
{
    char szName[0x50];
    ResetSlotKeepSettings__FPci(pslot, 0);
    func_001ABB10(pmc, pslot, szName);
    return func_001AC900(pmc, szName, pslot, CB_SAVE);
}
