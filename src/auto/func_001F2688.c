#include "m2c_prelude.h"
void func_001F2688(void *arg0, f32 fparg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x134);
    M2C_FIELD(arg0, f32 *, 0x13C) = fparg0;
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, s32 *, 0) == arg0)) {
        M2C_FIELD(temp_v1, f32 *, 0x20) = fparg0;
    }
}
