#include "m2c_prelude.h"
s32 PframeNew__Fv();                                /* extern */
M2C_UNK func_00256EE0(void *, s32);                 /* extern */
M2C_UNK AddRootFrame__3CGc(s32);                         /* extern */

// name: SafeHouse port (StartupSwSplice)
void StartupSwSplice__FP2SW(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3A14) = 1;
    func_00256EE0(arg0, PframeNew__Fv());
    AddRootFrame__3CGc(M2C_FIELD(arg0, s32 *, 0));
}
