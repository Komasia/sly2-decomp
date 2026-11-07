#include "m2c_prelude.h"
s32 func_00162670();                                /* extern */
M2C_UNK JobBegin__FP3JOB(void *);                      /* extern */
M2C_UNK func_00162F10(void *);                      /* extern */
M2C_UNK func_00165E10(M2C_UNK *, void *);           /* extern */
extern M2C_UNK g_sw;

// name: SafeHouse port (JobTaskReached)
void JobTaskReached__FP3JOBP4TASK(void *arg0, void *arg1) {
    if (func_00162670() != 0) {
        if (arg1 == M2C_FIELD(arg0, s32 *, 0x64)) {
            JobBegin__FP3JOB(arg0);
        }
        if (arg1 == M2C_FIELD(arg0, s32 *, 0x68)) {
            func_00162F10(arg0);
        }
        if (M2C_FIELD(arg1, s32 *, 0xB8) != -1) {
            func_00165E10(&g_sw, arg1);
        }
    }
}
