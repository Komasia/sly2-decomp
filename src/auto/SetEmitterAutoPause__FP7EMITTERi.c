#include "m2c_prelude.h"
void SetEmitterAutoPause__FP7EMITTERi(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x114) = arg1;
    M2C_FIELD(arg0, s32 *, 0xE0) = 1;
}
