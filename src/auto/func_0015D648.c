#include "m2c_prelude.h"
extern f32 D_002DDF0C;
extern M2C_UNK D_002E65E0;

// name: SafeHouse port (SetEpMode)
void SetEpMode__FP6EPMENUii(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_v0_2;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x11C);
    if ((temp_v1 != arg1) || (M2C_FIELD(arg0, s32 *, 0x120) != arg2)) {
        switch (temp_v1) {                          /* irregular */
        case 0:
            HudAutoSave__FP4SAVEi((s32) &D_002E65E0, 1);
            break;
        case 4:
        case 6:
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x114);
            M2C_FIELD(arg0, s32 *, 0x114) = -1;
            M2C_FIELD(arg0, s32 *, 0x110) = temp_v1_2;
            break;
        case 2:
            SetHint__FP6EPMENUi(arg0, 0);
            break;
        }
        if (arg1 == 2) {
            SetHint__FP6EPMENUi(arg0, -1);
            SetHint__FP6EPMENUi(arg0, 0);
        }
        M2C_FIELD(arg0, s32 *, 0x74) = -1;
        M2C_FIELD(arg0, s32 *, 0x70) = -1;
        M2C_FIELD(arg0, s32 *, 0x78) = -1;
        SetTimerTimers__FP5TIMER6TIMERS(arg0, 1);
        SetState__FP8SCREENRTi(arg0, 1);
        M2C_FIELD(arg0, s32 *, 0x11C) = arg1;
        M2C_FIELD(arg0, s32 *, 0x120) = arg2;
        M2C_FIELD(arg0, f32 *, 0x124) = (f32) D_002DDF0C;
        temp_v0 = IdPartCur__FP6EPMENU(arg0);
        if (temp_v0 != -1) {
            temp_v0_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v0_2, void (**)(s32, s32), 0x18C)(arg0 + M2C_FIELD(temp_v0_2, s16 *, 0x188), temp_v0);
        }
    }
}
