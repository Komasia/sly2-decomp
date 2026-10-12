#include "m2c_prelude.h"
s128 func_001A62E8(void *arg0) {
    s16 temp_a1;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    temp_a1 = M2C_FIELD(temp_v1, s16 *, 0xF8);
    return M2C_FIELD(M2C_FIELD(temp_v1, void *(**)(void *, s16), 0xFC)(arg0 + temp_a1, temp_a1), s128 *, 0x30);
}
