#include "m2c_prelude.h"
// name: SafeHouse port (FActorScriptAnim)
s32 FActorScriptAnim__FP2LO(void *arg0) {
    s16 temp_a1;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    temp_a1 = M2C_FIELD(temp_v1, s16 *, 0x2C8);
    return (u32) (M2C_FIELD(temp_v1, s32 (**)(void *, s16), 0x2CC)(arg0 + temp_a1, temp_a1) - 5) < 2U;
}
