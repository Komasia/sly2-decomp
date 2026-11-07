#include "m2c_prelude.h"
M2C_UNK SetMenuState__FP4MENUi(s32, M2C_UNK);                /* extern */
M2C_UNK ApplyGameSettings__FP8GAMESAVE(M2C_UNK *);                   /* extern */
extern M2C_UNK D_003D4A60;

void func_001AFF88(s32 arg0) {
    ApplyGameSettings__FP8GAMESAVE(&D_003D4A60);
    SetMenuState__FP4MENUi(arg0, 9);
}
