#include "m2c_prelude.h"
void func_00170C50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = PcmdAppend__FP7CMDLISTi3OID(arg0, 6, arg1);
    M2C_FIELD(temp_v0, s32 *, 8) = arg2;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg3;
}
