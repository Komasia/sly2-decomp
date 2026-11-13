#include "m2c_prelude.h"
void func_00162F10(s32 arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xB8) != 0) {
        SetJobSeq__FP3JOBi(arg0, 1);
        return;
    }
    JobCompleteClose__FP3JOB(arg0, arg1);
    func_00162FD0(arg0);
}
