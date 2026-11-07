#include "m2c_prelude.h"
M2C_UNK PruneJumpLedgeXps__FP5ACTOR(void *);                      /* extern */
M2C_UNK FindStepFloor__FP3ALO();                            /* extern */

// name: SafeHouse port (FindActorFloor)
void FindActorFloor__FP3ALO(void *arg0) {
    FindStepFloor__FP3ALO();
    if (M2C_FIELD(arg0, s32 *, 0x2DC) != -1) {
        PruneJumpLedgeXps__FP5ACTOR(arg0 + 0x2C0);
    }
}
