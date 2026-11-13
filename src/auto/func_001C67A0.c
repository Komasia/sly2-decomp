#include "m2c_prelude.h"
s32 func_00161798(M2C_UNK *);                       /* extern */
M2C_UNK func_001617E0(M2C_UNK *, s32);              /* extern */
extern M2C_UNK g_game;

// name: SafeHouse port (AddCoin 0x1C67A0: the game's coin count + 1)
void AddCoin(void) asm("AddCoin__Fv");
void AddCoin(void) {
    func_001617E0(&g_game, func_00161798(&g_game) + 1);
}
