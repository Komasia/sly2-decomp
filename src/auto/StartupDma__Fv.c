#include "m2c_prelude.h"
s32 sceDmaGetChan(M2C_UNK);                         /* extern */
M2C_UNK sceDmaReset(M2C_UNK);                       /* extern */
M2C_UNK sceGsResetPath();                           /* extern */
extern s32 D_002DE590;
extern s32 D_002DE594;
extern s32 D_002DE598;
extern s32 D_002DE59C;
extern s32 D_002DE5A0;

void StartupDma__Fv(void) {
    sceDmaReset(1);
    sceGsResetPath();
    D_002DE590 = sceDmaGetChan(0);
    D_002DE594 = sceDmaGetChan(1);
    D_002DE598 = sceDmaGetChan(2);
    D_002DE59C = sceDmaGetChan(8);
    D_002DE5A0 = sceDmaGetChan(9);
}
