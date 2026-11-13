#include "m2c_prelude.h"
void func_00170C90(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    void *temp_v0;

    temp_v0 = PcmdAppend__FP7CMDLISTi3OID(arg0, 7, arg1);
    M2C_FIELD(temp_v0, f32 *, 0x14) = fparg0;
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg2;
}
