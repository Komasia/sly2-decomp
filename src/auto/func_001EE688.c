#include "m2c_prelude.h"
M2C_UNK func_001ED8E0();                            /* extern */

void func_001EE688(void *arg0, void *arg1) {
    func_001ED8E0();
    M2C_FIELD(arg0, f32 *, 0x50) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
    M2C_FIELD(arg0, f32 *, 0x54) = (f32) M2C_FIELD(arg1, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x58) = (f32) M2C_FIELD(arg1, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x5C) = (f32) M2C_FIELD(arg1, f32 *, 0x18);
}
