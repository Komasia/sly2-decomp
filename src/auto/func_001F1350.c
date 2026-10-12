#include "m2c_prelude.h"
M2C_UNK func_001F08D0();                            /* extern */
M2C_UNK func_001F0D88(void *, M2C_UNK);             /* extern */

void func_001F1350(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    if ((M2C_FIELD(arg0, s32 *, 0x30) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0x10) & arg1)) {
        func_001F08D0();
        func_001F0D88(arg0, 0);
    }
}
