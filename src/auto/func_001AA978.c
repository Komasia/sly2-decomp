#include "m2c_prelude.h"
M2C_UNK InitSave__FP4SAVEii(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_001613F8(M2C_UNK *);                   /* extern */
extern M2C_UNK g_game;
extern M2C_UNK D_002E65E0;
extern s32 D_004425D8;

void func_001AA978(void) {
    func_001613F8(&g_game);
    D_004425D8 = -1;
    InitSave__FP4SAVEii(&D_002E65E0, 0, 0);
}
