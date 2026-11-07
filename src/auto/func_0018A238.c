#include "m2c_prelude.h"
M2C_UNK DrawActor__FP5ACTOR(void *);                      /* extern */
M2C_UNK DrawSlyHangPlace__FP3SLY();                            /* extern */

// name: SafeHouse port (DrawSlys)
void DrawSlys__FP2SW(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x18C8) == 3) {
        DrawSlyHangPlace__FP3SLY();
    }
    DrawActor__FP5ACTOR(arg0);
}
