#include "m2c_prelude.h"
s32 func_00161798(M2C_UNK *);                       /* extern */
M2C_UNK func_001617E0(M2C_UNK *, s32);              /* extern */
extern M2C_UNK g_game;

void func_001C67A0(void) {
    func_001617E0(&g_game, func_00161798(&g_game) + 1);
}
