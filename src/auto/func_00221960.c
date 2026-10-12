#include "m2c_prelude.h"
void func_00221960(void *arg0, f32 fparg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x118);
    M2C_FIELD(temp_v1, f32 *, 0x74) = fparg0;
    M2C_FIELD(temp_v1, f32 *, 0x70) = fparg0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x118), f32 *, 0x78) = 1.0f;
}
