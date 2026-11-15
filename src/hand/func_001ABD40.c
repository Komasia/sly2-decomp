/* func_001ABD40 (0x1ABD40): saves the game: the vibration setting applied, the game's progress copied into the game's
 * slot (CopyGameSaveForSlot from D_003E0EA8), then the card thread started with the PMF D_002A6C90 (func_001ABB60). */
#include "h5_mc.h"
struct MCPMF { int a, b; };
extern struct MCPMF g_pmfSave __asm__("D_002A6C90");  /* -> func_001ABB60 */
extern char g_gamesaveRead[] __asm__("D_003E0EA8");
void ApplyVibrationSetting__Fv(struct MC *pmc);
void CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(void *playout, void *pslot);
void CreateMemcardThread__FP7MEMCARDii(void *pmemcard, struct MCPMF pmf);
void func_001ABD40(struct MC *pmc)
{
    ApplyVibrationSetting__Fv(pmc);
    CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(g_gamesaveRead, pmc->pslotGame);
    CreateMemcardThread__FP7MEMCARDii(pmc->memcard, g_pmfSave);
}
