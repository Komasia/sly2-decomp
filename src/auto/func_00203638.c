#include "m2c_prelude.h"
M2C_UNK func_001333C0(s32, void *);                 /* extern */
M2C_UNK func_001A5C48();                            /* extern */

void func_00203638(void *arg0) {
    s32 temp_a0;

    func_001A5C48();
    temp_a0 = M2C_FIELD(arg0, s32 *, 0xEC);
    if (temp_a0 != 0) {
        func_001333C0(temp_a0, arg0);
    }
}
