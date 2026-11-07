#include "m2c_prelude.h"
// name: SafeHouse port (AddRefNoise)
void AddRefNoise__FP5NOISE(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + 1);
}
