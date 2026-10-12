#include "m2c_prelude.h"
M2C_UNK func_001EEF78();                            /* extern */

void func_00146758(void *arg0) {
    void *temp_a0;

    func_001EEF78();
    temp_a0 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(temp_a0, s32 *, 0x10E0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x10E0) & ~1);
}
