#include "m2c_prelude.h"
M2C_UNK func_002080A0(void *, void *);              /* extern */
M2C_UNK func_00209130(void *, void *);              /* extern */

void func_002080F0(void *arg0) {
    s32 var_s2;
    void *var_s1;

    var_s2 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x4C0) > 0) {
        var_s1 = arg0 + 0x4D0;
        do {
            func_00209130(var_s1, arg0);
            var_s2 += 1;
            var_s1 += 0x20;
        } while (var_s2 < M2C_FIELD(arg0, s32 *, 0x4C0));
    }
    func_002080A0(arg0, arg0 + 0xC10);
    func_002080A0(arg0, arg0 + 0x8D0);
    func_002080A0(arg0, arg0 + 0xA70);
}
