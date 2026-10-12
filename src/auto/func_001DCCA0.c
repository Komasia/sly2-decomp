#include "m2c_prelude.h"
M2C_UNK func_001DA770();                            /* extern */

void func_001DCCA0(void *arg0) {
    void *temp_v1;

    func_001DA770();
    temp_v1 = M2C_FIELD(arg0, void **, 0x24);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, s32 *, 0xB0) = 1;
    }
}
