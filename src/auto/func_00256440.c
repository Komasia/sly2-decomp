#include "m2c_prelude.h"
M2C_UNK __4CRef(void *);                            /* extern */
M2C_UNK func_0020C058(void *);                      /* extern */
extern M2C_UNK g_vtmurray;
extern M2C_UNK g_vtso;

void *func_00256440(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &g_vtso;
    __4CRef(arg0 + 0x80);
    M2C_FIELD(arg0, s32 *, 0x174) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &g_vtmurray;
    func_0020C058(arg0 + 0x1890);
    return arg0;
}
