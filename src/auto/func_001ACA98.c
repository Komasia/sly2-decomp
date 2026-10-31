#include "m2c_prelude.h"
M2C_UNK func_00129EC8(M2C_UNK *);                   /* extern */
s32 PvAllocSlot__FP8ALLOCREQ(void *);                          /* extern */
s32 func_002441C0(s32, s32, s32);                   /* extern */
s32 func_002442D8(s32, s32, s32);                   /* extern */
s32 func_00244570(s32, s32, s32, s32);              /* extern */
void CopyAb__FPvT0Ui(s32 arg0, s32 arg1, u32 arg2); /* static */
extern M2C_UNK D_002A6EA0;
extern M2C_UNK D_002A6EB0;
extern M2C_UNK D_002A6EB8;
extern M2C_UNK D_002A6EC8;
extern M2C_UNK D_002A6ED8;
extern M2C_UNK D_002A6EE0;
extern M2C_UNK D_002D36D0;
extern M2C_UNK D_002D3750;
extern M2C_UNK g_clock;
extern f32 D_002DDF0C;
extern M2C_UNK g_game;
extern M2C_UNK D_002E6550;
extern s32 D_002E6594;
extern M2C_UNK D_002E65E0;
extern M2C_UNK D_002E6604;
extern M2C_UNK D_002F633C;
extern s32 s_pvWorldMin;
extern s32 s_pvWorldMac;
extern s32 s_pvStackMin;
extern s32 s_pvStackMac;
extern M2C_UNK s_critsectStack;
extern s32 s_ipvStackCur;
extern M2C_UNK s_apvStackMin;
extern M2C_UNK D_003D4A60;
extern M2C_UNK D_003D9ED0;
extern M2C_UNK D_003D9EDC;
extern M2C_UNK D_003DA530;
extern M2C_UNK D_003DD490;
extern s32 D_003E0FAC;
extern s32 D_003E0FE4;
extern M2C_UNK D_47220F;

s32 func_001ACA98(s32 arg0) {
    func_001DA728(arg0);
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D3750;
    M2C_FIELD(arg0, s32 *, 0x20) = 0x52C;
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    func_001DA7D0(arg0);
    return arg0;
}
