#include "m2c_prelude.h"
s32 *__4CRefRC4CRef(s32 *arg0, s32 *arg1);           /* static */

// name: SafeHouse port (CFrame::AddParent)
void AddParent__6CFrameP6CFrame(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_v0 + 1);
    func_00256EE0((temp_v0 * 4) + arg0 + 0xC, arg1);
}
