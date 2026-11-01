#include "m2c_prelude.h"
s32 IsSwHandsOff__FP2SW(M2C_UNK *);                       /* extern */
extern M2C_UNK D_003DD490;

s32 func_001409B8(void) {
    return (IsSwHandsOff__FP2SW(&D_003DD490) != 0) ? 0 : -1;
}
