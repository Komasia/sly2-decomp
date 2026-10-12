#include "m2c_prelude.h"
s32 func_001D82B8(M2C_UNK *, M2C_UNK *);            /* extern */
M2C_UNK func_001DAF38(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_001FB2F8(s32, M2C_UNK);                /* extern */
s32 func_001FBB90(M2C_UNK);                         /* extern */
extern M2C_UNK D_003D4A60;
extern M2C_UNK D_003E0EA8;

void func_0014C200(void) {
    if (func_001D82B8(&D_003E0EA8, &D_003D4A60) >= 0x64) {
        func_001DAF38(0x1F, 1);
        return;
    }
    func_001FB2F8(func_001FBB90(0x3E), 0);
}
