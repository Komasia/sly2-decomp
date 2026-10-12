#include "m2c_prelude.h"
void func_00203FA0(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x204) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x204) = arg1;
        if (arg1 != 0) {
            M2C_FIELD(arg0, s32 *, 0x208) = 0;
        }
    }
}
