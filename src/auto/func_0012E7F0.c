#include "m2c_prelude.h"
M2C_UNK CutCm(M2C_UNK *) asm("CutCm__FP2CM");                   /* extern */
M2C_UNK Deactivate__5CPLCYP2LOPv(void *, s32, void *);         /* extern */
extern M2C_UNK g_cm;

// name: SafeHouse port (CPLOOKAT::Deactivate)
void Deactivate__8CPLOOKATP2LOPv(void *arg0, s32 arg1, void *arg2) {
    if (M2C_FIELD(arg0, s32 *, 0x10) == arg2) {
        if (M2C_FIELD(arg2, s32 *, 0x120) != 0) {
            CutCm(&g_cm);
        }
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
    }
    Deactivate__5CPLCYP2LOPv(arg0, arg1, arg2);
}
