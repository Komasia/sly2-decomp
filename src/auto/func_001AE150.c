#include "m2c_prelude.h"
extern s32 s_pvWorldMac;
extern s32 s_pvStackMin;

s32 func_001AE150(void) {
    return s_pvStackMin - s_pvWorldMac;
}
