#include "m2c_prelude.h"
// name: SafeHouse port (LinkObjNode)
void LinkObjNode__FP5WNODEi(s32 arg0, s32 arg1) {
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x138);
    M2C_FIELD(arg0, s32 *, 0x138) = arg1;
    WakeAlo__FP3ALO(arg0);
}
