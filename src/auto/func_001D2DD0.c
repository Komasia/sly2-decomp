#include "m2c_prelude.h"
extern f32 D_002A7834;

// name: SafeHouse port (BestContact)
s32 BestContact__FP12VEHICLEWHEELi(s32 arg0, s32 arg1) {
    f32 temp_f0;
    f32 var_f1;
    void *var_v0;
    void *var_v1;

    var_v1 = M2C_FIELD(arg1, void **, 8);
    var_f1 = D_002A7834;
    var_v0 = NULL;
    if (var_v1 != NULL) {
        do {
            temp_f0 = M2C_FIELD(var_v1, f32 *, 0x90);
            if (var_f1 < temp_f0) {
                var_f1 = temp_f0;
                var_v0 = var_v1;
            }
            var_v1 = M2C_FIELD(var_v1, void **, 0xAC);
        } while (var_v1 != NULL);
    }
    return (s32) var_v0;
}
