#include "m2c_prelude.h"
s32 FIsBasicDerivedFrom__FP5BASIC3CID(s32, M2C_UNK);                    /* extern */
M2C_UNK func_00143380(s32);                         /* extern */
M2C_UNK BroadcastTaskEvent__FP2SWiP2LO(M2C_UNK *, M2C_UNK, s32);     /* extern */
M2C_UNK JobSwitch__FP3JOB(s32);                         /* extern */
s32 FJobCur__FP3JOB();                                /* extern */
s32 func_001C4840(M2C_UNK *);                       /* extern */
extern M2C_UNK g_game;
extern M2C_UNK g_sw;

// name: SafeHouse port (JobBegin)
void JobBegin__FP3JOB(s32 arg0) {
    s32 temp_v0;

    if (FJobCur__FP3JOB() == 0) {
        BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x1C, arg0);
        temp_v0 = func_001C4840(&g_sw);
        if ((temp_v0 != 0) && (FIsBasicDerivedFrom__FP5BASIC3CID(temp_v0, 0x34) != 0)) {
            func_00143380(temp_v0);
        }
        JobSwitch__FP3JOB(arg0);
    }
}
