#include "m2c_prelude.h"
s32 sceDmaGetChan(M2C_UNK);                         /* extern */
M2C_UNK sceDmaReset(M2C_UNK);                       /* extern */
M2C_UNK sceGsResetPath();                           /* extern */
extern s32 g_pdcVif0;
extern s32 g_pdcVif1;
extern s32 g_pdcGif;
extern s32 g_pdcFromSpr;
extern s32 g_pdcToSpr;

void StartupDma__Fv(void) {
    sceDmaReset(1);
    sceGsResetPath();
    g_pdcVif0 = sceDmaGetChan(0);
    g_pdcVif1 = sceDmaGetChan(1);
    g_pdcGif = sceDmaGetChan(2);
    g_pdcFromSpr = sceDmaGetChan(8);
    g_pdcToSpr = sceDmaGetChan(9);
}
