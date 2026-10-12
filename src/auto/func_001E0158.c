#include "m2c_prelude.h"
void func_001E0158(void *arg0, s32 arg1) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0x68);
    if ((temp_a2 != NULL) && (*M2C_FIELD(temp_a2, s32 **, 0x30) == 9)) {
        M2C_FIELD(temp_a2, s32 *, 0x18) = arg1;
    }
}
