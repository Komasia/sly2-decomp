#include "m2c_prelude.h"
void *PregentEnsure__FP3ALO();                              /* extern */

void func_001F83B0(f32 fparg0) {
    void *temp_v0;

    temp_v0 = PregentEnsure__FP3ALO();
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, f32 *, 8) = fparg0;
    }
}
