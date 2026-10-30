#include "m2c_prelude.h"
M2C_UNK RemoveDlEntry__FP2DLPv(M2C_UNK *, s32);              /* extern */
M2C_UNK func_00156DE0(s32, M2C_UNK);                /* extern */
M2C_UNK OnLoRemove__FP2LO();                            /* extern */
extern M2C_UNK D_003E1468;

void func_00156D58(s32 arg0) {
    OnLoRemove__FP2LO();
    func_00156DE0(arg0, 1);
    RemoveDlEntry__FP2DLPv(&D_003E1468, arg0);
}
