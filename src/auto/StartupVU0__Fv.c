#include "m2c_prelude.h"
M2C_UNK FlushCache(M2C_UNK);                        /* extern */
M2C_UNK func_00241728(s32 *, M2C_UNK *);            /* extern */
M2C_UNK func_002417F0(s32 *, M2C_UNK, M2C_UNK);     /* extern */
extern M2C_UNK D_00259DF0;
extern s32 *D_002DE590;

void StartupVU0__Fv(void) {
    *D_002DE590 |= 0x40;
    FlushCache(0);
    func_00241728(D_002DE590, &D_00259DF0);
    func_002417F0(D_002DE590, 0, 0);
    *D_002DE590 &= ~0x40;
}
