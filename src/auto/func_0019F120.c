#include "m2c_prelude.h"
extern f32 D_002BF938;
extern f32 g_clock;

// name: SafeHouse port (UpdateGuardsFrozen)
void UpdateGuardsFrozen__FP2SW(s32 arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x4748) != 0) {
        if (D_002BF938 < (g_clock - M2C_FIELD(arg0, f32 *, 0x474C))) {
            func_0019F170(arg0, 0);
        }
    }
}
