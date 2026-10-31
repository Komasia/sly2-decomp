#include "m2c_prelude.h"
M2C_UNK func_0014C2D8(M2C_UNK *);                   /* extern */
M2C_UNK func_001870D0();                            /* extern */
M2C_UNK func_00187150(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK scePadInit(M2C_UNK);                        /* extern */
extern M2C_UNK D_002DDEC0;
extern M2C_UNK g_joy;

void func_00187030(void) {
    func_001870D0();
    scePadInit(0);
    func_00187150(&g_joy, 0, 0);
    func_0014C2D8(&D_002DDEC0);
}
