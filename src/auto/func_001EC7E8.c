#include "m2c_prelude.h"
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_003DA790;
extern s32 D_003DCFA0;
extern M2C_UNK D_003DCFA8;

void func_001EC7E8(void) {
    D_003DCFA0 = 0;
    D_003DA790 = 0;
    memset(&D_003DCFA8, 0, 0x40);
}
