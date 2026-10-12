#include "m2c_prelude.h"
s32 func_001E0128(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x68);
    if ((temp_a1 == NULL) || (*M2C_FIELD(temp_a1, s32 **, 0x30) != 9)) {
        return 0;
    }
    return M2C_FIELD(temp_a1, s32 *, 0x18);
}
