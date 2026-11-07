#include "m2c_prelude.h"
M2C_UNK DrawActor__FP5ACTOR(void *);                      /* extern */
M2C_UNK func_00190D10();                            /* extern */

void func_0018A238(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x18C8) == 3) {
        func_00190D10();
    }
    DrawActor__FP5ACTOR(arg0);
}
