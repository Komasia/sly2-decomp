#include "m2c_prelude.h"
M2C_UNK RemoveNoise__FP5NOISE();                            /* extern */
extern f32 g_clock;

// name: SafeHouse port (ExpireNoises)
void ExpireNoises__FPv(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), f32 *, 0x60);
    if (temp_f2 >= 0.0f) {
        if ((M2C_FIELD(arg0, f32 *, 0x4C) + temp_f2) < g_clock) {
            RemoveNoise__FP5NOISE();
        }
    }
}
