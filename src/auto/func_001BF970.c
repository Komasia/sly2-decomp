#include "m2c_prelude.h"
s32 func_001BF970(void *arg0, s32 arg1) {
    return (s32) (arg1 - M2C_FIELD(arg0, s32 *, 4)) >> 5;
}
