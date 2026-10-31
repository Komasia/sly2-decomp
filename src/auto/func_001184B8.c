#include "m2c_prelude.h"
/* Warning: missing "jr $ra" in last block of func_00119C30 (initial). */

M2C_UNK CopyAb__FPvT0Ui(s32, s32, s32);             /* extern */
s32 PvAllocSlot__FP8ALLOCREQ(void *, s32, s32);                /* extern */
void Decompress__18CBinaryInputStream(void *arg0);                     /* static */
extern M2C_UNK D_002BBAF0;
extern M2C_UNK D_002BBB10;
extern M2C_UNK D_002BBB20;
extern M2C_UNK D_002CA5A0;
extern M2C_UNK D_002CA5C0;
extern void *g_psliFirst;
extern void *s_pdliFirst;

void func_001184B8(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK **, 0x30) = &D_002CA5A0;
    if (arg1 & 1) {
        __builtin_delete();
    }
}
