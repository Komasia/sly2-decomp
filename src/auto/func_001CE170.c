#include "m2c_prelude.h"
extern s32 D_003E115C;

void UpdateRipgBounds__FP4RIPG(s32 arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), s128 *, 0) = (s128) M2C_FIELD(arg0, s128 *, 0x170);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), s128 *, 0x10) = (s128) M2C_FIELD(arg0, s128 *, 0x180);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), s128 *, 0x20) = (s128) M2C_FIELD(arg0, s128 *, 0x190);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), f32 *, 0x30) = (f32) M2C_FIELD(arg0, f32 *, 0x1A0);
    D_003E115C = 1;
    UnmarkOxaDirty1__FP3ALO(arg0);
}
