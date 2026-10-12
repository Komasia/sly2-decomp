#include "m2c_prelude.h"
M2C_UNK func_001CE920();                            /* extern */
extern s128 D_002C1F90;
extern s128 D_002C1FA0;

void func_001D0108(void *arg0) {
    func_001CE920();
    M2C_FIELD(arg0, f32 *, 0x18) = 0.5f;
    M2C_FIELD(arg0, s128 *, 0x30) = (s128) D_002C1F90;
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) D_002C1FA0;
}
