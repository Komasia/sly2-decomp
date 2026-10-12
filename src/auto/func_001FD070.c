#include "m2c_prelude.h"
s32 func_001FD070(void *arg0, s32 arg1) {
    return (s32) (arg1 - M2C_FIELD(arg0, s32 *, 0xFC)) >> 2;
}
