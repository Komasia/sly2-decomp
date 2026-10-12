#include "m2c_prelude.h"
M2C_UNK FlushCache(M2C_UNK);                        /* extern */
M2C_UNK func_00241728(s32 *, M2C_UNK *);            /* extern */
M2C_UNK func_002417F0(s32 *, M2C_UNK, M2C_UNK);     /* extern */
extern M2C_UNK D_0025E050;
extern s32 *D_002DE594;

void StartupVU1__Fv(void) {
    *D_002DE594 |= 0x40;
    FlushCache(0);
    func_00241728(D_002DE594, &D_0025E050);
    func_002417F0(D_002DE594, 0, 0);
    *D_002DE594 &= ~0x40;
}
