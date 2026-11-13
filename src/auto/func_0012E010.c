#include "m2c_prelude.h"
// name: SafeHouse port (CTRLTARGET::Fetch)
void Fetch__10CTRLTARGET(s32 arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), f32 *, 0xA8) = (f32) M2C_FIELD(arg0, f32 *, 0x1C);
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xC0) = (s128) M2C_FIELD(arg0, s128 *, 0x20);
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xD0) = (s128) M2C_FIELD(arg0, s128 *, 0x30);
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), s16 *, 0x9A) = 2;
    ResetXfParams__FP2XFPv(M2C_FIELD(arg0, s32 *, 4), (s32) M2C_FIELD(arg0, void **, 8));
}
