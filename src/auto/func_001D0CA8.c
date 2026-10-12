#include "m2c_prelude.h"
M2C_UNK func_001CE920();                            /* extern */
extern s128 D_002C1F40;

void func_001D0CA8(void *arg0) {
    func_001CE920();
    M2C_FIELD(arg0, f32 *, 0x18) = 5.0f;
    M2C_FIELD(arg0, s128 *, 0xA0) = (s128) D_002C1F40;
}
