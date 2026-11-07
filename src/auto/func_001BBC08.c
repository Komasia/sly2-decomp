#include "m2c_prelude.h"
void *PitemNew__FP2LOi(s32, M2C_UNK);                  /* extern */
s32 func_001BBE18();                                /* extern */
M2C_UNK SetAloSoesByTag__FP3ALOi(s32, s32);                    /* extern */

void func_001BBC08(s32 arg0, s32 arg1) {
    if (func_001BBE18() == 0) {
        SetAloSoesByTag__FP3ALOi(arg0, arg1);
        return;
    }
    M2C_FIELD(PitemNew__FP2LOi(arg0, 4), s32 *, 4) = arg1;
}
