#include "m2c_prelude.h"
void *PwreGetWrCur__FP2WR4ENSK4WREK(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x54) == 0) {
        return NULL;
    }
    if (arg1 == 1) {
        M2C_FIELD(arg0, s32 *, 0x8FC) = arg1;
    }
    return arg0 + ((M2C_FIELD(arg0, s32 *, 0x6E0) * 0xD0) + 0x60);
}
