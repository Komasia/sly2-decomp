#include "m2c_prelude.h"
void func_0012DFE0(void *arg0, s128 *arg1, void *arg2) {
    if (arg1 != NULL) {
        *arg1 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xC0);
    }
    if (arg2 != NULL) {
        M2C_FIELD(arg2, s32 *, 8) = 0;
        M2C_FIELD(arg2, s32 *, 4) = 0;
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
}
