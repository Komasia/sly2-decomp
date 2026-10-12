#include "m2c_prelude.h"
M2C_UNK func_001F5078(void *);                      /* extern */

void func_00209790(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    M2C_FIELD(arg0, s32 *, 0) = 0;
    temp_v1 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    temp_v0 = temp_v1 + 0x190;
    M2C_FIELD(temp_v0, s32 *, 8) = 0;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    M2C_FIELD(temp_v1, s32 *, 0x190) = 0;
    func_001F5078(M2C_FIELD(arg0, void **, 0xC));
}
