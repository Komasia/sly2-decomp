#include "m2c_prelude.h"
void func_002129E8(s32 arg0) {
    SetTimerTimers__FP5TIMER6TIMERS(arg0, 1);
    if (M2C_FIELD(arg0, s32 *, 0x78) == -1) {
        SetState__FP8SCREENRTi(arg0, 1);
    }
}
