#include "m2c_prelude.h"
M2C_UNK LockJob__FP5AIJOB(void *);                      /* extern */
M2C_UNK UnlockJob__FP5AIJOB();                            /* extern */
extern f32 g_clock;

// name: SafeHouse port (JOBMURRAYATTACK::SetState)
void SetState__15JOBMURRAYATTACKi(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x30);
    if (arg1 != temp_v0) {
        if (temp_v0 == 2) {
            UnlockJob__FP5AIJOB();
        }
        M2C_FIELD(arg0, s32 *, 0x30) = arg1;
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) g_clock;
        if (arg1 == 2) {
            LockJob__FP5AIJOB(arg0);
        }
    }
}
