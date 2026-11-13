#include "m2c_prelude.h"
extern f32 g_clock;

// name: SafeHouse port (SetAbilityState)
void SetAbilityState__FP5ACTORP6ABSLOTi(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_v0 = M2C_FIELD(arg1, s32 *, 4);
    if (temp_v0 != arg2) {
        if (temp_v0 == 1) {
            temp_v0_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v0_2, void (**)(s32, s32), 0x334)(arg0 + M2C_FIELD(temp_v0_2, s16 *, 0x330), M2C_FIELD(arg1, s32 *, 0));
        }
        M2C_FIELD(arg1, s32 *, 4) = arg2;
        M2C_FIELD(arg1, f32 *, 8) = (f32) g_clock;
        switch (arg2) {                             /* irregular */
        case 2:
            temp_v0_3 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v0_3, void (**)(s32, s32), 0x324)(arg0 + M2C_FIELD(temp_v0_3, s16 *, 0x320), M2C_FIELD(arg1, s32 *, 0));
            M2C_FIELD(arg1, s32 *, 4) = 0;
            return;
        case 1:
            temp_v0_4 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v0_4, void (**)(s32, s32), 0x324)(arg0 + M2C_FIELD(temp_v0_4, s16 *, 0x320), M2C_FIELD(arg1, s32 *, 0));
            break;
        }
    }
}
