#include "m2c_prelude.h"
f32 GSuck__FPv();                                /* extern */
M2C_UNK SetSuck__FPvf(s32, f32);                    /* extern */

void func_00154D88(s32 arg0, f32 fparg0) {
    SetSuck__FPvf(arg0, GSuck__FPv() + fparg0);
}
