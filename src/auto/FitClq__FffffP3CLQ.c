#include "m2c_prelude.h"
void FitClq__FffffP3CLQ(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    f32 temp_f13;
    f32 temp_f15;

    temp_f13 = fparg1 - fparg0;
    M2C_FIELD(arg0, f32 *, 0) = fparg0;
    temp_f15 = (((fparg3 - fparg0) / fparg2) - temp_f13) / (fparg2 - 1.0f);
    M2C_FIELD(arg0, f32 *, 8) = temp_f15;
    M2C_FIELD(arg0, f32 *, 4) = (f32) (temp_f13 - temp_f15);
}
