#include "m2c_prelude.h"
M2C_UNK Decref(s32, s32, s32) asm("Decref__4CRef");               /* static */
M2C_UNK InitTag(s32, M2C_UNK) asm("InitTag__4CRef");                /* static */
extern s128 D_002A2DD0;

// name: SafeHouse port (CTRLPOS::Fetch)
void Fetch__7CTRLPOS(s32 arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xC0) = (s128) M2C_FIELD(arg0, s128 *, 0x20);
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xD0) = (s128) D_002A2DD0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0x9A) = (u16) M2C_FIELD(arg0, u16 *, 0x1C);
    ResetXfParams__FP2XFPv(M2C_FIELD(arg0, s32 *, 4), (s32) M2C_FIELD(arg0, void **, 8));
}
