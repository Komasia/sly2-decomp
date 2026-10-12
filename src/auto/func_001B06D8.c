#include "m2c_prelude.h"
M2C_UNK func_001AF390(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_003D9ED0;

void func_001B06D8(void *arg0) {
    func_001AF390(&D_003D9ED0, M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC));
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 2);
    }
}
