#include "m2c_prelude.h"
/* Warning: missing "jr $ra" in last block of func_00119C30 (initial). */

/* Warning: missing "jr $ra" in last block of func_0011B040 (initial). */

M2C_UNK CopyAb__FPvT0Ui(s32, s32, s32);             /* extern */
M2C_UNK func_00117898();                            /* extern */
s32 func_001AE318(s32 *, s32, s32);                 /* extern */
extern u8 D_002A4150;
extern M2C_UNK D_002AA6A1;
extern M2C_UNK D_002BBAF0;
extern M2C_UNK D_002BBB10;
extern M2C_UNK D_002BBB20;
extern void *D_002DD2F8;
extern void *D_002DD2FC;

void func_001179D8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg2;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 2);
}
