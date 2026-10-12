#include "m2c_prelude.h"
M2C_UNK func_001F35F8(f32);                         /* extern */

void func_001F35C8(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f12;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0xE8);
    temp_f0 = M2C_FIELD(temp_v0, f32 *, 0xD0);
    temp_f12 = fparg0 / temp_f0;
    M2C_FIELD(temp_v0, f32 *, 0xD0) = (f32) (temp_f0 * temp_f12);
    func_001F35F8(temp_f12);
}
