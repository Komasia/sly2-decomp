#include "m2c_prelude.h"
M2C_UNK func_002311B0();                            /* extern */

void func_00258620(void *arg0) {
    s32 *temp_v1;

    func_002311B0();
    temp_v1 = M2C_FIELD(arg0, s32 **, 0xE4);
    *temp_v1 += 1;
}
