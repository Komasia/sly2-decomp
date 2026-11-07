#include "m2c_prelude.h"
M2C_UNK func_00162908(s32);                         /* extern */
M2C_UNK func_001629A0(s32);                         /* extern */
s32 FJobCur__FP3JOB();                                /* extern */
extern s32 D_003E0F9C;

// name: SafeHouse port (JobSwitch)
void JobSwitch__FP3JOB(s32 arg0) {
    if (FJobCur__FP3JOB() == 0) {
        if (D_003E0F9C != 0) {
            func_00162908(D_003E0F9C);
        }
        func_001629A0(arg0);
    }
}
