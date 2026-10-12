#include "m2c_prelude.h"
void *func_001F8300();                              /* extern */

void func_001F8470(f32 fparg0) {
    void *temp_v0;

    temp_v0 = func_001F8300();
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, f32 *, 4) = fparg0;
    }
}
