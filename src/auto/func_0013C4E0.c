#include "m2c_prelude.h"
// name: SafeHouse port (ReturnThrownBooty)
void ReturnThrownBooty__FP2LO(s32 arg0) {
    s32 temp_s1;
    s32 temp_s2;

    if (M2C_FIELD(arg0, s32 *, 0x184) == 5) {
        temp_s1 = M2C_FIELD(arg0, s32 *, 0x15C);
        M2C_FIELD(arg0, s32 *, 0x15C) = 0;
        temp_s2 = M2C_FIELD(arg0, s32 *, 0x158);
        SetBootyState__FP2LOi(arg0, 0);
        if ((temp_s1 != 0) && (func_001A61A0(temp_s1) != 0)) {
            M2C_FIELD(arg0, s32 *, 0x15C) = temp_s1;
            M2C_FIELD(arg0, s32 *, 0x158) = temp_s2;
            SetBootyState__FP2LOi(arg0, 1);
        }
    }
}
