#include "m2c_prelude.h"
M2C_UNK SetActorWatchTarget__FP5ACTORG9VU_VECTOR(s32, s128);                   /* extern */
M2C_UNK Enter__9JOBFOLLOW();                            /* extern */

void func_00144B58(void *arg0) {
    Enter__9JOBFOLLOW();
    SetActorWatchTarget__FP5ACTORG9VU_VECTOR(M2C_FIELD(arg0, s32 *, 0x10) + 0xFD0, M2C_FIELD(arg0, s128 *, 0x80));
}
