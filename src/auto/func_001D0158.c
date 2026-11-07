#include "m2c_prelude.h"
s128 PosOfLo__FP2LO(s32);                            /* extern */

void func_001D0158(void *arg0) {
    M2C_FIELD(arg0, s128 *, 0x80) = (s128) M2C_FIELD(arg0, s128 *, 0x70);
    M2C_FIELD(arg0, s128 *, 0x70) = PosOfLo__FP2LO(M2C_FIELD(arg0, s32 *, 0xF0));
}
