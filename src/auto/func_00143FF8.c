#include "m2c_prelude.h"
// name: SafeHouse port (EndActorScriptAnim)
void EndActorScriptAnim__FP5ACTOR(s32 arg0) {
    void *temp_v0;

    if (FActorScriptAnim__FP2LO(arg0) != 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_v0, void (**)(s32, M2C_UNK), 0x2C4)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x2C0), 0);
    }
}
