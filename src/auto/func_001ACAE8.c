#include "m2c_prelude.h"
M2C_UNK func_001ACB58(void *, s32);                 /* extern */
M2C_UNK func_001DA770();                            /* extern */

void func_001ACAE8(void *arg0) {
    s32 temp_a1;
    void *temp_a0;

    func_001DA770();
    temp_a0 = M2C_FIELD(arg0, void **, 0x24);
    if (temp_a0 != NULL) {
        M2C_FIELD(temp_a0, s32 *, 0xB0) = 1;
        temp_a1 = M2C_FIELD(arg0, s32 *, 0x40);
        if (temp_a1 != -1) {
            func_001ACB58(arg0, temp_a1);
        }
    }
}
