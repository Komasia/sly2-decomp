#include "m2c_prelude.h"
void func_0014F5F8(void *arg0, f32 fparg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x314);
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, f32 *, 4) = fparg0;
    }
}
