#include "m2c_prelude.h"
M2C_UNK func_0014F610();                            /* extern */

void func_0014F630(void *arg0, f32 fparg0) {
    void *temp_v0;

    func_0014F610();
    temp_v0 = M2C_FIELD(arg0, void **, 0x314);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, f32 *, 8) = fparg0;
    }
}
