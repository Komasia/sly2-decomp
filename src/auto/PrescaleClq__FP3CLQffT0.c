#include "m2c_prelude.h"
void PrescaleClq__FP3CLQffT0(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg1, f32 *, 8) = (f32) (M2C_FIELD(arg0, f32 *, 8) * fparg0 * fparg0);
    M2C_FIELD(arg1, f32 *, 4) = (f32) ((2.0f * M2C_FIELD(arg0, f32 *, 8) * fparg0 * fparg1) + (M2C_FIELD(arg0, f32 *, 4) * fparg0));
    M2C_FIELD(arg1, f32 *, 0) = (f32) ((M2C_FIELD(arg0, f32 *, 8) * fparg1 * fparg1) + (M2C_FIELD(arg0, f32 *, 4) * fparg1) + M2C_FIELD(arg0, f32 *, 0));
}
