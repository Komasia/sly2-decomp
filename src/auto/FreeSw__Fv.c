#include "m2c_prelude.h"
extern s32 s_pvWorldMin;
extern s32 s_pvWorldMac;

void FreeSw__Fv(void) {
    s_pvWorldMac = s_pvWorldMin;
}
